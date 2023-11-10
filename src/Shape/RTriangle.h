#pragma once

#include <wx/wx.h>

struct RTriangle
{
    wxPoint2DDouble drag;
    wxPoint2DDouble origin;
    wxColour color;
    int width;
};