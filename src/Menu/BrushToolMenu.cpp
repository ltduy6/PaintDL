#include "BrushToolMenu.h"

BrushToolMenu::BrushToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::Brush)
{
    colorMenu.SetUpColorMenu(parent, sizer);
    sizeMenu.SetUpSizeMenu(parent, sizer, "Size");
}

void BrushToolMenu::ShowMenu(bool show)
{
    colorMenu.Show(show);
    sizeMenu.Show(show);
}
