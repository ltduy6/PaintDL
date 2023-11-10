#pragma once

#include <wx/wx.h>
#include <vector>

struct Path
{
    wxColour color;
    int width;
    std::vector<wxPoint2DDouble> points;
};