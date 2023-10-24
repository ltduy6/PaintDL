#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include <string>

class RoundedButton : public wxButton
{
public:
    RoundedButton(wxWindow *parent, wxWindowID id, std::string fileName, const wxSize &size = wxDefaultSize, const wxPoint &pos = wxDefaultPosition, long style = wxBU_AUTODRAW);

    wxSize DoGetBestSize() const override
    {
        return FromDIP(wxSize(35, 35));
    }

private:
    void OnPaint(wxPaintEvent &event);
    void OnHover(wxMouseEvent &event);
    void OnLeave(wxMouseEvent &event);

private:
    std::string path{"src/Assets/"};
    bool isHovered{false};
};