#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <functional>

#include <string>

class RoundedButton : public wxButton
{
public:
    RoundedButton(wxWindow *parent, wxWindowID id, wxString name, const wxSize &size = wxDefaultSize, const wxPoint &pos = wxDefaultPosition, long style = wxBU_AUTODRAW);

    void SetFinished(bool isFinished);
    void AddCallback(std::function<void()> callback);

private:
    void OnPaint(wxPaintEvent &event);
    void OnHover(wxMouseEvent &event);
    void OnLeave(wxMouseEvent &event);
    void OnMoveUp(wxMouseEvent &event);
    void OnMoveDown(wxMouseEvent &event);

private:
    wxString m_name{};
    std::vector<std::function<void()>> callbacks;
    bool isHovered{false};
    bool isHold{false};
};