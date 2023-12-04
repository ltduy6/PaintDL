#pragma once

#include "ToolMenu.h"
#include "ImageMenu.h"

class SelectionToolMenu : public ToolMenu
{
public:
    SelectionToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~SelectionToolMenu() = default;

private:
    ImageMenu imageMenu;
};