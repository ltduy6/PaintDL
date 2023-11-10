#pragma once

#include "SelectablePane.h"
#include "../StrokeSettings.h"

class ShapePane : public SelectablePane
{
public:
    ShapePane(wxWindow *parent, wxWindowID id, ToolType type, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
    ToolType type;

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
};