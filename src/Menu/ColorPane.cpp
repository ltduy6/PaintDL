#include "ColorPane.h"

ColorPane::ColorPane(wxWindow *parent, wxWindowID id, const wxColor &paneColor, const wxPoint &pos, const wxSize &size)
    : SelectablePane(parent, id, pos, size), color(paneColor), colorType(ColorType::Single)
{
}

void ColorPane::SetSingleColour(const wxColour &newColor)
{
    color = newColor;
    colorType = ColorType::Single;
}

void ColorPane::SetGradientColour(const wxGraphicsGradientStops &newGradient)
{
    gradient = newGradient;
    colorType = ColorType::Gradient;
}

void ColorPane::DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const
{
    gc->SetPen(wxPen(color));
    if (colorType == ColorType::Gradient)
        gc->SetBrush(gc->CreateLinearGradientBrush(rect.GetX(), rect.GetY(), rect.GetX() + rect.GetWidth(), rect.GetY(), gradient));
    else
        gc->SetBrush(wxBrush(color));
    gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);
}