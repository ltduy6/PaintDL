#pragma once

#include "SelectablePane.h"

class ColorPane : public SelectablePane
{
public:
    ColorPane(wxWindow *parent, wxWindowID id, const wxColor &paneColor, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    wxColour color;

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
};