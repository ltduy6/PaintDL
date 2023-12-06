#pragma once

#include "ToolMenu.h"

class MoveToolMenu : public ToolMenu
{
public:
    MoveToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~MoveToolMenu() = default;
};