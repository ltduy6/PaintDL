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

    wxPanel *docPanel;
    wxScrolled<wxPanel> *controlsPanel;

    wxStaticText *textSize;
    wxSizer *penWidthSizer;

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

    return true;
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

        this->Bind(
            wxEVT_MENU, [canvas](wxCommandEvent &)
            { canvas->ShowExportDialog(); },
            idExport);

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

    bool isDark = wxSystemSettings::GetAppearance().IsDark();
    controlsPanel->SetBackgroundColour(wxColour(isDark ? darkBackground : lightBackground));

    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto textColor = new wxStaticText(controlsPanel, wxID_ANY, "Colors");
    mainSizer->Add(textColor, 0, wxALL, FromDIP(5));

    auto colorPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    colorMenu.SetUpColorMenu(controlsPanel, colorPaneSizer, this);
    mainSizer->Add(colorPaneSizer, 0, wxALL, FromDIP(5));

    auto textTools = new wxStaticText(controlsPanel, wxID_ANY, "Tools");
    mainSizer->Add(textTools, 0, wxALL, FromDIP(5));

    auto toolPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    toolMenu.SetUpToolMenu(controlsPanel, toolPaneSizer, [this]()
                           { ResetControls(); });
    mainSizer->Add(toolPaneSizer, 0, wxALL, FromDIP(5));

    textSize = new wxStaticText(controlsPanel, wxID_ANY, "Size");
    mainSizer->Add(textSize, 0, wxALL, FromDIP(5));

    penWidthSizer = new wxWrapSizer(wxHORIZONTAL);
    sizeMenu.SetUpSizeMenu(controlsPanel, penWidthSizer);
    mainSizer->Add(penWidthSizer, 0, wxALL, FromDIP(5));

    auto textShape = new wxStaticText(controlsPanel, wxID_ANY, "Shapes");
    mainSizer->Add(textShape, 0, wxALL, FromDIP(5));

    auto shapePaneSizer = new wxWrapSizer(wxHORIZONTAL);
    shapeMenu.SetUpShapeMenu(controlsPanel, shapePaneSizer, [this]()
                             { ResetControls(); });
    mainSizer->Add(shapePaneSizer, 0, wxALL, FromDIP(5));

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
    auto menuBar = new wxMenuBar;

    auto fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW);
    fileMenu->Append(wxID_OPEN);
    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_SAVEAS);
    idExport = fileMenu->Append(wxID_ANY, "&Export...")->GetId();

    fileMenu->Append(wxID_EXIT);

    menuBar->Append(fileMenu, "&File");

    auto editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO);
    editMenu->Append(wxID_REDO);
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT);
    editMenu->Append(wxID_COPY);
    editMenu->Append(wxID_PASTE);
    editMenu->Append(wxID_DELETE);
    editMenu->AppendSeparator();
    editMenu->Append(wxID_SELECTALL);

    menuBar->Append(editMenu, "&Edit");

    SetMenuBar(menuBar);
}

void MyFrame::ResetControls()
{
    shapeMenu.SelectShapePane();
    toolMenu.SelectToolPane();
}
