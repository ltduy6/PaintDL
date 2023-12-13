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
    ZoomIn,
    Move,
    Font,
    Gradient,
    NoFill,
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
    wxColour textColor{*wxBLACK};
    wxFont font{10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL};
    wxGraphicsGradientStops gradientStops;

    bool isGradient{false};
    int width{3};
    int outlineWidth{3};
    int fontSize{10};
    double selectionHandleWidth;

    ShapeType currentShape{ShapeType::Path};
    ToolType currentTool{ToolType::Brush};
};