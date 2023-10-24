#pragma once

#include "SelectableMenu.h"

class ColorMenu : public SelectableMenu
{
public:
    ColorMenu(wxWindow *parent, wxWindowID id, const wxColor &paneColor, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    wxColour color;

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
};