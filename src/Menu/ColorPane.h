#pragma once

#include "SelectablePane.h"

class ColorPane : public SelectablePane
{
public:
    ColorPane(wxWindow *parent, wxWindowID id, const wxColor &paneColor, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
    void SetSingleColour(const wxColour &newColor);
    void SetGradientColour(const wxGraphicsGradientStops &newGradient);
    wxColour color;

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;

private:
    enum class ColorType
    {
        Single,
        Gradient
    };

private:
    wxGraphicsGradientStops gradient;
    ColorType colorType;
};