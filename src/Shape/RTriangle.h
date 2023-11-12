#pragma once

#include <wx/wx.h>

struct RTriangle
{
    wxRect2DDouble rect;
    wxPoint2DDouble drag;
    wxPoint2DDouble origin;
    wxColour color;
    int width;
};