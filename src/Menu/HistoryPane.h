#pragma once

#include <wx/wx.h>
#include <wx/wx.h>

#include <wx/graphics.h>
#include <wx/settings.h>
#include <wx/dcbuffer.h>
#include <wx/dc.h>
#include <wx/dcgraph.h>

#include "SelectablePane.h"

class HistoryPane : public SelectablePane
{
public:
    HistoryPane(wxWindow *parent, wxString name, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
    ~HistoryPane() override;
    void SetActive(bool isActive);

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;

private:
    wxString name;
    wxDouble *width;
    wxDouble *height;
    bool isActive{true};
};