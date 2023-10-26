#pragma once

#include <wx/wx.h>

#include <wx/graphics.h>
#include <wx/settings.h>
#include <wx/dcbuffer.h>
#include <wx/dc.h>
#include <wx/dcgraph.h>

class SelectableMenu : public wxWindow
{
public:
    SelectableMenu(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    wxSize DoGetBestSize() const override
    {
        return FromDIP(wxSize(35, 35));
    }

    bool selected = false;

protected:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const = 0;

private:
    void OnPaint(wxPaintEvent &event);
    void OnMouseEnter(wxMouseEvent &event);
};
