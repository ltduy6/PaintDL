#include "RoundedButton.h"

RoundedButton::RoundedButton(wxWindow *parent, wxWindowID id, wxString name, const wxSize &size, const wxPoint &pos, long style)
    : wxButton(parent, id, name, pos, size, style), m_name(name)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &RoundedButton::OnPaint, this);
    Bind(wxEVT_ENTER_WINDOW, &RoundedButton::OnHover, this);
    Bind(wxEVT_LEAVE_WINDOW, &RoundedButton::OnLeave, this);
    Bind(wxEVT_LEFT_DOWN, &RoundedButton::OnMoveDown, this);
    Bind(wxEVT_LEFT_UP, &RoundedButton::OnMoveUp, this);
}

void RoundedButton::SetFinished(bool isFinished)
{
    isHold = isFinished;
}

void RoundedButton::AddCallback(std::function<void()> callback)
{
    callbacks.push_back(callback);
}

void RoundedButton::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(this->GetParent()->GetBackgroundColour()));
    dc.Clear();

    auto gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        wxRect rc{0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight()};
        wxColour bkColor(wxColour(90, 90, 90));
        wxColour textColor(wxColour(231, 246, 242));
        wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);

        gc->SetBrush(wxBrush(bkColor));
        gc->SetPen(wxPen(bkColor, 1, wxPENSTYLE_SOLID));
        gc->DrawRectangle(rc.x, rc.y, rc.width, rc.height);

        gc->SetFont(font, textColor);
        wxDouble *width = new wxDouble;
        wxDouble *height = new wxDouble;
        gc->GetTextExtent(m_name, width, height);
        gc->DrawText(_(m_name), rc.x + 5, rc.y + (rc.height - *height) / 2);
        delete gc;
    }
}

void RoundedButton::OnHover(wxMouseEvent &event)
{
    isHovered = true;
}

void RoundedButton::OnLeave(wxMouseEvent &event)
{
    isHovered = false;
    isHold = false;
}

void RoundedButton::OnMoveUp(wxMouseEvent &event)
{
    if (isHovered)
    {
        isHold = false;
        Refresh();
        for (const auto &callback : callbacks)
        {
            callback();
        }
    }
}

void RoundedButton::OnMoveDown(wxMouseEvent &event)
{
    isHold = true;
}
