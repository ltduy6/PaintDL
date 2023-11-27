#pragma once

#include "SelectablePane.h"
#include "../StrokeSettings.h"

class ToolsPane : public SelectablePane
{
public:
    ToolsPane(wxWindow *parent, wxWindowID id, ToolType type, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
    void setToolType(ToolType type);
    ToolType getToolType() const;

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
    ToolType m_type;
    wxBitmap m_bitmap;
};