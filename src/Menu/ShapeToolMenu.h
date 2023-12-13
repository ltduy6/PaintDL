#pragma once

#include "ToolMenu.h"
#include "ShapeMenu.h"
#include "ColorMenu.h"
#include "SizeMenu.h"

class ShapeToolMenu : public ToolMenu
{
public:
    ShapeToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~ShapeToolMenu() = default;

private:
    ShapeMenu shapeMenu;
    ColorMenu colorOutline;
    ColorMenu colorFill;
    SizeMenu sizeMenu;
    wxWindow *parent;
};