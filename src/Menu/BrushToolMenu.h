#pragma once

#include "ToolMenu.h"
#include "ColorMenu.h"
#include "SizeMenu.h"

class BrushToolMenu : public ToolMenu
{
public:
    BrushToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~BrushToolMenu() = default;

private:
    ColorMenu colorMenu;
    SizeMenu sizeMenu;
};