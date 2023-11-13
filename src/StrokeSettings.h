#pragma once
#include <wx/wx.h>

enum class ToolType
{
    Brush,
    Transform,
    Rotate,
    CustomColor,
    None
};

enum class ShapeType
{
    Path,
    Rect,
    Circle,
    ITriangle,
    RTriangle,
    Diamond,
    None
};

struct StrokeSettings
{
    wxColour color{*wxBLACK};
    int width{3};
    double selectionHandleWidth;

    ShapeType currentShape{ShapeType::Path};
    ToolType currentTool{ToolType::Brush};
};