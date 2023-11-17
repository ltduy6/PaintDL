#include "HistoryPanel.h"

void HistoryPanel::SetUp(wxWindow *parent, wxSizer *sizer)
{
    historyPanel = new wxScrolled<wxPanel>(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    historySizer = new wxBoxSizer(wxVERTICAL);
    historyPanel->SetScrollRate(0, parent->FromDIP(10));
    historyPanel->SetBackgroundColour(wxColour(44, 51, 51));
    historyPanel->SetSizer(historySizer);

    auto text = new wxStaticText(parent, wxID_ANY, "History Panel");
    text->SetForegroundColour(wxColour(231, 246, 242));
    sizer->Add(text, 0, wxALL, parent->FromDIP(5));
    sizer->Add(historyPanel, 1, wxEXPAND | wxALL, parent->FromDIP(5));
}

void HistoryPanel::AddHistoryItem(wxCommandProcessor *historyProcessor, HistoryPane *button)
{
    wxString name = historyProcessor->GetCurrentCommand()->GetName();
    size_t id = historyProcessor->GetCommands().GetCount();
    buttons.push_back(button);
    button->AddCallback([this, historyProcessor, id]()
                        {
        int currentIndex = HistoryPane::currentIndex;
        if (id < currentIndex)
        {
            for (int i = 0; i < currentIndex - id; i++)
                historyProcessor->Undo();
        }
        else
        {
            for (int i = 0; i < id - currentIndex; i++)
                historyProcessor->Redo();
        } });
    historySizer->Add(button, 0, wxEXPAND | wxALL, 2);
    historyPanel->Layout();
    historyPanel->GetParent()->Layout();
    historyPanel->Scroll(0, historyPanel->GetVirtualSize().y);
}

void HistoryPanel::ClearHistory()
{
    if (historySizer)
    {
        historySizer->Clear();
        historyPanel->Layout();
        historyPanel->GetParent()->Layout();
    }
}

HistoryPane *HistoryPanel::createHistoryPane(wxString name)
{
    auto button = new HistoryPane(historyPanel, name);
    return button;
}
