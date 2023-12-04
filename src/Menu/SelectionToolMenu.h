#pragma once

#include "ToolMenu.h"
#include "ImageMenu.h"

class SelectionToolMenu : public ToolMenu
{
public:
    SelectionToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    void CallRotate(DrawingCanvas *canvas);
    virtual void ItemPopCallback() override;
    ~SelectionToolMenu() = default;

private:
    ImageMenu imageMenu;
};