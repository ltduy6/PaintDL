#pragma once
#include <wx/wx.h>

enum class ToolType
{
    Path,
    Rect,
    Circle,
    ITriangle,
    RTriangle,
    Diamond,
    Brush,
    None
};

struct StrokeSettings
{
    wxColour color{*wxBLACK};
    int width{3};

    ToolType currentShape{ToolType::Path};
    ToolType currentTool{ToolType::Brush};
};