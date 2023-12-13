#pragma once

#include "ToolMenu.h"
#include "ColorMenu.h"
#include "SizeMenu.h"
#include "FontMenu.h"

class TextToolMenu : public ToolMenu
{
public:
    TextToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~TextToolMenu() = default;

private:
    FontMenu fontMenu;
};