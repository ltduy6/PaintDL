#pragma once
#include <wx/wx.h>

enum class ToolType
{
    Brush = 1,
    Shape = 2,
    Transform = 4,
    Rotate = 8,
    CustomColor = 16,
    Text = 32,
    ZoomIn = 64,
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
    wxColour outlineColor{*wxBLACK};
    wxColour fillColor{*wxBLACK};

    int width{3};
    double selectionHandleWidth;

    ShapeType currentShape{ShapeType::Path};
    ToolType currentTool{ToolType::Brush};
};