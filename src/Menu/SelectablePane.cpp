#include "SelectablePane.h"

SelectablePane::SelectablePane(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SelectablePane::OnPaint, this);
    Bind(wxEVT_ENTER_WINDOW, &SelectablePane::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &SelectablePane::OnMouseLeave, this);
    Bind(wxEVT_LEFT_UP, &SelectablePane::OnMouseClick, this);
}

void SelectablePane::AddCallback(std::function<void()> callback)
{
    callbacks.push_back(callback);
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

        if (selected)
        {
            gc->SetPen(wxPen(wxColour(231, 246, 242), FromDIP(1)));
            gc->SetBrush(*wxTRANSPARENT_BRUSH);

            gc->DrawRoundedRectangle(selectionRect.GetX(), selectionRect.GetY(), selectionRect.GetWidth(), selectionRect.GetHeight(), roundness);
        }

        if (isHover)
        {
            gc->SetBrush(wxColor(89, 101, 101));
            gc->DrawRoundedRectangle(selectionRect.GetX(), selectionRect.GetY(), selectionRect.GetWidth(), selectionRect.GetHeight(), roundness);
        }

        DrawContent(gc, contentRect, roundness);

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

void SelectablePane::OnMouseClick(wxMouseEvent &event)
{
    for (auto &callback : callbacks)
    {
        callback();
    }
}
