#pragma once

#include <wx/wx.h>
#include <wx/wx.h>

#include <wx/graphics.h>
#include <wx/settings.h>
#include <wx/dcbuffer.h>
#include <wx/dc.h>
#include <wx/dcgraph.h>

class HistoryPane : public wxWindow
{
public:
    HistoryPane(wxWindow *parent, wxString name, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    wxSize DoGetBestSize() const override
    {
        return FromDIP(wxSize(35, 20));
    }

private:
    void OnPaint(wxPaintEvent &event);

private:
    wxString name;
};