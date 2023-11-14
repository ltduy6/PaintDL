#pragma once
#include <wx/wx.h>
#include <wx/cmdproc.h>

#include "HistoryPane.h"
#include "RoundedButton.h"

class HistoryPanel
{
public:
    void SetUp(wxWindow *controlsPanel, wxBoxSizer *mainSizer, wxFrame *frame);
    void AddHistoryItem(wxString name, std::function<void()> callback);
    void ClearHistory();

private:
    wxScrolled<wxPanel> *historyPanel{nullptr};
    wxBoxSizer *historySizer{nullptr};
};