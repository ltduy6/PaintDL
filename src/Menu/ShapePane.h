#pragma once

#include "SelectablePane.h"
#include "../StrokeSettings.h"

class ShapePane : public SelectablePane
{
public:
    ShapePane(wxWindow *parent, wxWindowID id, ShapeType type, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
    ShapeType type;

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
};