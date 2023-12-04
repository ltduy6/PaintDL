#include "ShapeToolMenu.h"

ShapeToolMenu::ShapeToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::Shape), parent(parent)
{
    shapeMenu.SetUpShapeMenu(parent, sizer);
    colorOutline.SetUpColorMenu(parent, sizer, 1, "Outline");
    colorFill.SetUpColorMenu(parent, sizer, 1, "Fill");
}

void ShapeToolMenu::ShowMenu(bool show)
{
    shapeMenu.Show(show);
    colorOutline.Show(show);
    colorFill.Show(show);
}
