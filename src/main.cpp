#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>
#include <wx/colordlg.h>

#include <string>
#include <vector>

#include "MyApp.h"
#include "Menu/ColorMenu.h"
#include "DrawingCanvas.h"
#include "Menu/RoundedButton.h"

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    wxPanel *BuildControlsPanel(wxWindow *parent);

    void SetupColorPanes(wxWindow *parent, wxSizer *sizer);

    void SelectColorPane(ColorMenu *pane);

    void OnChooseColor(wxCommandEvent &event);

private:
    std::vector<ColorMenu *> colorPanes{};
    ColorMenu *selectedColorPane{};

    DrawingCanvas *canvas;

    const std::vector<std::string> niceColors = {"#000000", "#ffffff", "#fd7f6f",
                                                 "#7eb0d5", "#b2e061", "#bd7ebe",
                                                 "#ffb55a", "#ffee65", "#beb9db",
                                                 "#fdcce5", "#8bd3c7"};

    const int penCount = 6;

    const std::string lightBackground = "#f4f3f3";
    const std::string darkBackground = "#2c2828";
};

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

void MyFrame::SetupColorPanes(wxWindow *parent, wxSizer *sizer)
{
    wxSize size{};
    for (const auto &color : niceColors)
    {
        auto colorPane = new ColorMenu(parent, wxID_ANY, wxColour(color));
        size = colorPane->DoGetBestSize();

        colorPane->Bind(wxEVT_LEFT_DOWN, [this, colorPane](wxMouseEvent &event)
                        { SelectColorPane(colorPane); });

        colorPanes.push_back(colorPane);
        sizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
    }
    auto button = new RoundedButton(parent, wxID_ANY, "color-wheel.png", size);
    button->Bind(wxEVT_BUTTON, &MyFrame::OnChooseColor, this);
    sizer->Add(button, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
}

wxPanel *MyFrame::BuildControlsPanel(wxWindow *parent)
{
    auto controlsPanel = new wxScrolled<wxPanel>(parent, wxID_ANY);
    controlsPanel->SetScrollRate(0, FromDIP(10));

    bool isDark = wxSystemSettings::GetAppearance().IsDark();
    controlsPanel->SetBackgroundColour(wxColour(isDark ? darkBackground : lightBackground));

    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto text = new wxStaticText(controlsPanel, wxID_ANY, "Colors");
    mainSizer->Add(text, 0, wxALL, FromDIP(5));

    auto colorPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    SetupColorPanes(controlsPanel, colorPaneSizer);

    mainSizer->Add(colorPaneSizer, 0, wxALL, FromDIP(5));

    text = new wxStaticText(controlsPanel, wxID_ANY, "Pens");
    mainSizer->Add(text, 0, wxALL, FromDIP(5));

    mainSizer->AddStretchSpacer();
    mainSizer->AddSpacer(FromDIP(2));

    controlsPanel->SetSizer(mainSizer);

    return controlsPanel;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    splitter->SetMinimumPaneSize(FromDIP(150));

    auto controlsPanel = BuildControlsPanel(splitter);
    canvas = new DrawingCanvas(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    splitter->SplitVertically(controlsPanel, canvas);
    splitter->SetSashPosition(FromDIP(220));

    this->SetSize(FromDIP(800), FromDIP(500));
    this->SetMinSize({FromDIP(400), FromDIP(200)});

    SelectColorPane(colorPanes[0]);
}

void MyFrame::SelectColorPane(ColorMenu *pane)
{
    for (auto colorPane : colorPanes)
    {
        colorPane->selected = (colorPane == pane);
        colorPane->Refresh();
    }
    canvas->SetPenColor(pane->color);
    selectedColorPane = pane;
}

void MyFrame::OnChooseColor(wxCommandEvent &event)
{
    wxColourData data;
    data.SetChooseFull(true);
    for (int i = 0; i < 16; ++i)
    {
        wxColour color(i * 16, i * 16, i * 16);
        data.SetCustomColour(i, color);
    }
    wxColourDialog dialog(this, &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxColourData retData = dialog.GetColourData();
        wxColour col = retData.GetColour();
        canvas->SetPenColor(col);
        selectedColorPane->color = col;
        selectedColorPane->Refresh();
    }
}
