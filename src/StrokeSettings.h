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
    Transform,
    Rotate,
    None
};

enum class ShapeType
{
    Path,
    Rect,
    Circle,
    ITriangle,
    RTriangle,
    Diamond
};

struct StrokeSettings
{
    wxColour color{*wxBLACK};
    int width{3};
    double selectionHandleWidth;

    ToolType currentShape{ToolType::Path};
    ToolType currentTool{ToolType::Brush};
};