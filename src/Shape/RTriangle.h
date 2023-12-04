#pragma once

#include <wx/wx.h>

struct RTriangle
{
    wxRect2DDouble rect;
    wxPoint2DDouble drag;
    wxPoint2DDouble origin;
    wxColour outlineColor;
    wxColour fillColor;
    int width;
};