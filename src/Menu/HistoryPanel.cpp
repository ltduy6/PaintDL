#include "HistoryPanel.h"

void HistoryPanel::SetUp(wxWindow *controlsPanel, wxBoxSizer *mainSizer, wxFrame *frame)
{
    historyPanel = new wxScrolled<wxPanel>(controlsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    historySizer = new wxBoxSizer(wxVERTICAL);
    historyPanel->SetScrollRate(0, frame->FromDIP(10));
    historyPanel->SetBackgroundColour(wxColour(44, 51, 51));
    historyPanel->SetSizer(historySizer);

    auto text = new wxStaticText(controlsPanel, wxID_ANY, "History Panel");
    text->SetForegroundColour(wxColour(231, 246, 242));
    mainSizer->Add(text, 0, wxALL, frame->FromDIP(5));
    mainSizer->Add(historyPanel, 1, wxEXPAND | wxALL, frame->FromDIP(5));
}

void HistoryPanel::AddHistoryItem(wxString name, std::function<void()> callback)
{

    auto button = new RoundedButton(historyPanel, wxID_ANY, name);
    button->SetBackgroundColour(wxColour(90, 90, 90));
    button->Bind(wxEVT_BUTTON, [callback](wxCommandEvent &event)
                 { callback(); });
    historySizer->Add(button, 0, wxEXPAND | wxALL, 2);
    historyPanel->Layout();
    historyPanel->GetParent()->Layout();
    historyPanel->Scroll(0, historyPanel->GetVirtualSize().y);
}

void HistoryPanel::ClearHistory()
{
    if (historySizer)
    {
        historySizer->Clear(true);
        historyPanel->Layout();
        historyPanel->GetParent()->Layout();
    }
}
