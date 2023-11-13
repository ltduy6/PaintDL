#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>
#include <wx/colordlg.h>
#include <functional>

#include <string>
#include <vector>
#include <chrono>

#include "myapp.h"

#include "Menu/RoundedButton.h"
#include "Menu/ColorMenu.h"
#include "Menu/SizeMenu.h"
#include "Menu/ShapeMenu.h"
#include "Menu/ToolMenu.h"
#include "Menu/ImageMenu.h"

#include "Canvas/DrawingCanvas.h"
#include "DrawingDocument.h"
#include "DrawingView.h"

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxDocParentFrame
{
public:
    MyFrame(wxDocManager *manager, wxFrame *frame, wxWindowID id, const wxString &title,
            const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    void SetupCanvasForView(DrawingView *view);

private:
    wxScrolled<wxPanel> *BuildControlsPanel(wxWindow *parent);

    void BuildMenuBar();
    void ResetControls();

private:
    ColorMenu colorMenu{};
    SizeMenu sizeMenu{};
    ShapeMenu shapeMenu{};
    ToolMenu toolMenu{};
    ImageMenu imageMenu{};

    wxPanel *docPanel;
    wxScrolled<wxPanel> *controlsPanel;

    wxStaticText *textSize;
    wxSizer *penWidthSizer;

    wxMenu *editMenu{nullptr};
    DrawingCanvas *m_canvas{nullptr};

    int idExport{};

    const std::string lightBackground = "#f4f3f3";
    const std::string darkBackground = "#2c2828";
};

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    SetAppDisplayName("PaintDL");

    m_docManager.reset(new wxDocManager);
    m_docManager->SetMaxDocsOpen(1);

    new wxDocTemplate(m_docManager.get(), "Drawing",
                      "*.pxz", "", "pxz", "DrawingDocument", "DrawingView",
                      CLASSINFO(DrawingDocument),
                      CLASSINFO(DrawingView));

    m_frame = new MyFrame(m_docManager.get(), nullptr, wxID_ANY, wxGetApp().GetAppDisplayName());
    m_frame->Show(true);

    m_strokeSettings.selectionHandleWidth = m_frame->FromDIP(10);

    return true;
}

int MyApp::OnExit()
{
    return wxApp::OnExit();
}

StrokeSettings &MyApp::GetStrokeSettings()
{
    return wxGetApp().m_strokeSettings;
}

void MyApp::SetupCanvasForView(DrawingView *view)
{
    wxGetApp().m_frame->SetupCanvasForView(view);
}

void MyFrame::SetupCanvasForView(DrawingView *view)
{
    if (docPanel->GetChildren().size() > 0)
    {
        docPanel->GetSizer()->Clear(true);
    }

    if (view != nullptr)
    {
        auto canvas = new DrawingCanvas(docPanel, view, wxID_ANY, wxDefaultPosition, wxDefaultSize);
        docPanel->GetSizer()->Add(canvas, 1, wxEXPAND);

        imageMenu.CallRotate(canvas);
        shapeMenu.AddCallBack([canvas]()
                              { canvas->ReFreshCanvas(); });
        toolMenu.AddCallBack([canvas]()
                             { canvas->ReFreshCanvas(); });
        m_canvas = canvas;

        view->GetDocument()->GetCommandProcessor()->SetEditMenu(editMenu);
        view->GetDocument()->GetCommandProcessor()->Initialize();

        this->Bind(wxEVT_MENU, [&](wxCommandEvent &event)
                   {
            if(event.GetId() == wxID_UNDO)
            {
                view->GetDocument()->GetCommandProcessor()->Undo();
            }
            else if(event.GetId() == wxID_REDO)
            {
                view->GetDocument()->GetCommandProcessor()->Redo();
            } });

        view->SetFrame(this);
    }
    else
    {
        this->SetTitle(wxGetApp().GetAppDisplayName());
    }

    docPanel->Layout();
}

wxScrolled<wxPanel> *MyFrame::BuildControlsPanel(wxWindow *parent)
{
    auto controlsPanel = new wxScrolled<wxPanel>(parent, wxID_ANY);
    controlsPanel->SetScrollRate(0, FromDIP(10));

    controlsPanel->SetBackgroundColour(wxColour(44, 51, 51));

    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto addGroup = [this, controlsPanel, mainSizer](const wxString &title)
    {
        auto text = new wxStaticText(controlsPanel, wxID_ANY, title);
        text->SetForegroundColour(wxColour(231, 246, 242));
        mainSizer->Add(text, 0, wxALL, FromDIP(5));

        auto wrapSizer = new wxWrapSizer(wxHORIZONTAL);
        if (title == "Colors")
        {
            colorMenu.SetUpColorMenu(controlsPanel, wrapSizer, this);
        }
        else if (title == "Tools")
        {
            toolMenu.SetUpToolMenu(controlsPanel, wrapSizer, [this]()
                                   { ResetControls(); });
        }
        else if (title == "Image")
        {
            imageMenu.SetUpImageMenu(controlsPanel, wrapSizer);
        }
        else if (title == "Size")
        {
            sizeMenu.SetUpSizeMenu(controlsPanel, wrapSizer);
        }
        else if (title == "Shapes")
        {
            shapeMenu.SetUpShapeMenu(controlsPanel, wrapSizer, [this]()
                                     { ResetControls(); });
        }
        else
        {
            throw std::runtime_error("Unknown group title");
        }

        mainSizer->Add(wrapSizer, 0, wxALL, FromDIP(5));
    };

    addGroup("Colors");
    addGroup("Tools");
    addGroup("Image");
    addGroup("Size");
    addGroup("Shapes");

    controlsPanel->SetSizer(mainSizer);

    return controlsPanel;
}

MyFrame::MyFrame(wxDocManager *manager, wxFrame *frame, wxWindowID id, const wxString &title,
                 const wxPoint &pos, const wxSize &size)
    : wxDocParentFrame(manager, frame, id, title, pos, size)
{
    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    splitter->SetMinimumPaneSize(FromDIP(150));

    controlsPanel = BuildControlsPanel(splitter);
    docPanel = new wxPanel(splitter, wxID_ANY);
    docPanel->SetSizer(new wxBoxSizer(wxVERTICAL));

    splitter->SplitVertically(controlsPanel, docPanel);
    splitter->SetSashPosition(FromDIP(100));

    this->SetSize(FromDIP(800), FromDIP(500));
    this->SetMinSize({FromDIP(400), FromDIP(200)});

    BuildMenuBar();
}

void MyFrame::BuildMenuBar()
{
    constexpr int ExportId = 10001;
    auto menuBar = new wxMenuBar;

    auto fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW);
    fileMenu->Append(wxID_OPEN);
    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_SAVEAS);
    fileMenu->Append(wxID_EXIT);
    fileMenu->Append(ExportId, "&Export...");
    fileMenu->Bind(
        wxEVT_MENU, [&](wxCommandEvent &)
        {
        if (m_canvas)
        {
            m_canvas->ShowExportDialog();
        } },
        ExportId);
    menuBar->Append(fileMenu, "&File");

    editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO);
    editMenu->Append(wxID_REDO);

    menuBar->Append(editMenu, "&Edit");

    SetMenuBar(menuBar);
}

void MyFrame::ResetControls()
{
    shapeMenu.SelectShapePane();
    toolMenu.SelectToolPane();
}
