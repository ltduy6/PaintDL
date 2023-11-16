#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <functional>

#include <string>

class RoundedButton : public wxWindow
{
public:
    typedef std::shared_ptr<RoundedButton> Ptr;

public:
    RoundedButton(wxWindow *parent, wxWindowID id, wxString name, const wxSize &size = wxDefaultSize, const wxPoint &pos = wxDefaultPosition, long style = wxBU_AUTODRAW);
    ~RoundedButton() override;
    void SetFinished(bool isFinished);
    void AddCallback(std::function<void()> callback);
    void SetHovered(bool isHovered);

    wxSize DoGetBestSize() const override
    {
        return wxSize(25, 20);
    }

private:
    void OnPaint(wxPaintEvent &event);
    void Onclick(wxMouseEvent &event);

private:
    wxString m_name{};
    std::vector<std::function<void()>> callbacks;
    bool isHovered{true};
    bool isHold{false};
};