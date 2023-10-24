#include "SizeMenu.h"

SizeMenu::SizeMenu(wxWindow *parent, wxWindowID id, int width, const wxPoint &pos, const wxSize &size)
    : SelectableMenu(parent, id, pos, size), width(width)
{
}

void SizeMenu::DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const
{
    
}
