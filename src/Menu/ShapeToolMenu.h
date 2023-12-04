#pragma once

#include "ToolMenu.h"
#include "ShapeMenu.h"
#include "ColorMenu.h"

class ShapeToolMenu : public ToolMenu
{
public:
    ShapeToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~ShapeToolMenu() = default;

private:
    void SetUpColor(wxWindow *parent, wxSizer *sizer);

private:
    ShapeMenu shapeMenu;
    ColorMenu colorOutline;
    ColorMenu colorFill;
    wxWindow *parent;
};