#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>
#include <wx/colordlg.h>
#include <functional>

#include <string>
#include <vector>
#include <chrono>

#include "myapp.h"

#include "Menu/HistoryPanel.h"
#include "Menu/MenuBar.h"

#include "Canvas/DrawingCanvas.h"
#include "DrawingDocument.h"
#include "DrawingView.h"
#include "CanvasInfoPanel.h"

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxDocParentFrame
{
public:
    MyFrame(wxDocManager *manager, wxFrame *frame, wxWindowID id, const wxString &title,
            const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    void SetupCanvasForView(DrawingView *view);

private:
    wxScrolled<wxPanel> *BuildControlsPanel(wxSplitterWindow *parent);
    wxPanel *BuildHistoryPanel(wxWindow *parent);

    void BuildMenuBar();
    void ResetControls();

private:
    HistoryPanel historyPanelHolder{};
    MenuBar menuBarHolder{};

    wxPanel *docPanel;
    wxPanel *zoomPanel;
    wxScrolled<wxPanel> *m_controlsPanel;
    wxPanel *m_historyPanel;

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
        historyPanelHolder.ClearHistory();
    }

    if (view != nullptr)
    {
        auto canvas = new DrawingCanvas(docPanel, view, historyPanelHolder, wxID_ANY, wxDefaultPosition, wxDefaultSize);
        docPanel->GetSizer()->Add(canvas, 1, wxEXPAND);

        m_canvas = canvas;

        view->GetDocument()->GetCommandProcessor()->SetEditMenu(editMenu);
        view->GetDocument()->GetCommandProcessor()->Initialize();

        view->SetFrame(this);
    }
    else
    {
        this->SetTitle(wxGetApp().GetAppDisplayName());
    }
    docPanel->Layout();
}

wxScrolled<wxPanel> *MyFrame::BuildControlsPanel(wxSplitterWindow *parent)
{
    auto controlsPanel = new wxScrolled<wxPanel>(parent, wxID_ANY);
    auto toolsPanel = new wxScrolled<wxPanel>(parent, wxID_ANY);

    controlsPanel->SetScrollRate(0, FromDIP(10));
    toolsPanel->SetScrollRate(0, FromDIP(10));

    controlsPanel->SetBackgroundColour(wxColour(83, 83, 83));
    toolsPanel->SetBackgroundColour(wxColour(83, 83, 83));

    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    controlsPanel->SetSizer(mainSizer);
    auto toolSizer = new wxWrapSizer(wxVERTICAL);
    toolsPanel->SetSizer(toolSizer);

    menuBarHolder.SetUp(controlsPanel, mainSizer, toolsPanel, toolSizer);

    controlsPanel->Layout();
    mainSizer->Fit(controlsPanel);

    toolsPanel->Layout();
    toolSizer->Fit(toolsPanel);

    parent->SplitVertically(toolsPanel, controlsPanel);
    parent->SetSashPosition(FromDIP(40));
    return controlsPanel;
}

wxPanel *MyFrame::BuildHistoryPanel(wxWindow *parent)
{
    auto historyPanel = new wxPanel(parent, wxID_ANY);
    historyPanel->SetBackgroundColour(wxColour(83, 83, 83));
    historyPanelHolder.SetUp(historyPanel);
    return historyPanel;
}

MyFrame::MyFrame(wxDocManager *manager, wxFrame *frame, wxWindowID id, const wxString &title,
                 const wxPoint &pos, const wxSize &size)
    : wxDocParentFrame(manager, frame, id, title, pos, size)
{
    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_NOSASH);
    wxSplitterWindow *splitterControl = new wxSplitterWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER);
    wxSplitterWindow *splitterTool = new wxSplitterWindow(splitterControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER);

    splitter->SetMinimumPaneSize(FromDIP(150));

    m_controlsPanel = BuildControlsPanel(splitterTool);
    m_historyPanel = BuildHistoryPanel(splitterControl);

    splitterControl->SplitHorizontally(splitterTool, m_historyPanel);
    splitterControl->SetSashPosition(FromDIP(500));

    docPanel = new wxPanel(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
    docPanel->SetSizer(new wxBoxSizer(wxVERTICAL));
    docPanel->SetBackgroundColour(wxColour(40, 40, 40));

    splitter->SplitVertically(splitterControl, docPanel);
    splitter->SetSashPosition(FromDIP(100));

    this->SetSize(FromDIP(800), FromDIP(500));
    this->SetMinSize({FromDIP(400), FromDIP(200)});
    this->Maximize();

    BuildMenuBar();
}

void MyFrame::BuildMenuBar()
{
    constexpr int ExportId = 10001;
    constexpr int HistoryId = 10002;
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
