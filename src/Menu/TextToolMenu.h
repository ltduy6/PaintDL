#pragma once

#include "ToolMenu.h"
#include "ColorMenu.h"

class TextToolMenu : public ToolMenu
{
public:
    TextToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~TextToolMenu() = default;

private:
    ColorMenu colorMenu;
};