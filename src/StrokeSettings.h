#pragma once
#include <wx/wx.h>

enum class ToolType
{
    Brush,
    Shape,
    Transform,
    Rotate,
    CustomColor,
    Text,
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
    Text,
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