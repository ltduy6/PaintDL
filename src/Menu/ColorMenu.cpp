#include "ColorMenu.h"

ColorMenu::ColorMenu(wxWindow *parent, wxWindowID id, const wxColor &paneColor, const wxPoint &pos, const wxSize &size)
    : SelectableMenu(parent, id, pos, size), color(paneColor)
{
}

void ColorMenu::DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const
{
    gc->SetPen(wxPen(color));
    gc->SetBrush(wxBrush(color));
    gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);
}