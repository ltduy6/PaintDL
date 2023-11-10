#include "SelectablePane.h"

SelectablePane::SelectablePane(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SelectablePane::OnPaint, this);
    Bind(wxEVT_ENTER_WINDOW, &SelectablePane::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &SelectablePane::OnMouseLeave, this);
}

void SelectablePane::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(this->GetParent()->GetBackgroundColour()));
    dc.Clear();

    auto gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        wxRect selectionRect{0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight()};
        selectionRect.Deflate(FromDIP(1));

        wxRect contentRect = selectionRect;
        contentRect.Deflate(FromDIP(2));

        const auto roundness = FromDIP(4);

        DrawContent(gc, contentRect, roundness);

        if (isHover || selected)
        {
            gc->SetPen(wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE_PEN : *wxBLACK_PEN);
            gc->SetBrush(*wxTRANSPARENT_BRUSH);

            gc->DrawRoundedRectangle(selectionRect.GetX(), selectionRect.GetY(), selectionRect.GetWidth(), selectionRect.GetHeight(), roundness);
        }

        delete gc;
    }
}

void SelectablePane::OnMouseEnter(wxMouseEvent &event)
{
    isHover = true;
    Refresh();
}

void SelectablePane::OnMouseLeave(wxMouseEvent &event)
{
    isHover = false;
    Refresh();
}
