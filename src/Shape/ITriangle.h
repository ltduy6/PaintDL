#pragma once

#include <wx/wx.h>

struct ITriangle
{
    wxRect2DDouble rect;
    wxColour outlineColor;
    wxColour fillColor;
    int width;
    wxGraphicsGradientStops gradientStops;
    bool isGradient;
};