#include "RoundedButton.h"

RoundedButton::RoundedButton(wxWindow *parent, wxWindowID id, std::string fileName, const wxSize &size, const wxPoint &pos, long style)
    : wxButton(parent, id, wxEmptyString, pos, size, style)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &RoundedButton::OnPaint, this);
    Bind(wxEVT_ENTER_WINDOW, &RoundedButton::OnHover, this);
    Bind(wxEVT_LEAVE_WINDOW, &RoundedButton::OnLeave, this);
    path += fileName;
}

void RoundedButton::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(this->GetParent()->GetBackgroundColour()));
    dc.Clear();

    auto gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        wxRect selectionRect{0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight()};
        selectionRect.Deflate(FromDIP(2));

        const auto roundness = FromDIP(4);

        bool isDark = wxSystemSettings::GetAppearance().IsDark();
        gc->SetPen(*wxTRANSPARENT_PEN);
        gc->SetBrush(isHovered ? *wxLIGHT_GREY : *wxTRANSPARENT_BRUSH);
        gc->DrawRoundedRectangle(selectionRect.GetX(), selectionRect.GetY(), selectionRect.GetWidth(), selectionRect.GetHeight(), roundness);

        wxBitmap bitmap(path, wxBITMAP_TYPE_PNG);
        if (bitmap.IsOk())
        {
            gc->DrawBitmap(bitmap, selectionRect.GetX(), selectionRect.GetY(), selectionRect.GetWidth(), selectionRect.GetHeight());
        }

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
}
