#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>

struct Circle
{
    wxRect2DDouble rect;
    wxColour outlineColor;
    wxColour fillColor;
    int width;
    wxGraphicsGradientStops gradientStops;
    bool isGradient;
};