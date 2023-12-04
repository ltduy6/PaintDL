#pragma once
#include <wx/wx.h>
#include <wx/cmdproc.h>
#include <wx/wrapsizer.h>

#include "HistoryPane.h"
#include "RoundedButton.h"

class HistoryPanel
{
public:
    void SetUp(wxWindow *parent);
    void AddHistoryItem(wxCommandProcessor *historyProcessor, HistoryPane *button);
    void ClearHistory();
    HistoryPane *createHistoryPane(wxString name);

private:
    wxScrolled<wxPanel> *historyPanel{nullptr};
    wxBoxSizer *historySizer{nullptr};
    std::vector<HistoryPane *> buttons;
    size_t currentCommand{0};
};