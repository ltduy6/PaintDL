#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <functional>

#include <string>

class RoundedButton : public wxButton
{
public:
    RoundedButton(wxWindow *parent, wxWindowID id, std::string fileName, const wxSize &size = wxDefaultSize, const wxPoint &pos = wxDefaultPosition, long style = wxBU_AUTODRAW);

    wxSize DoGetBestSize() const override
    {
        return FromDIP(wxSize(35, 35));
    }

    void SetFinished(bool isFinished);
    void AddCallback(std::function<void()> callback);

private:
    void OnPaint(wxPaintEvent &event);
    void OnHover(wxMouseEvent &event);
    void OnLeave(wxMouseEvent &event);
    void OnMoveUp(wxMouseEvent &event);
    void OnMoveDown(wxMouseEvent &event);

private:
    std::string path{"src/Assets/"};
    std::vector<std::function<void()>> callbacks;
    bool isHovered{false};
    bool isHold{false};
};