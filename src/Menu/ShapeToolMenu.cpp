#include "ShapeToolMenu.h"

ShapeToolMenu::ShapeToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::Shape), parent(parent)
{
    shapeMenu.SetUpShapeMenu(parent, sizer);
    colorOutline.SetUpColorMenu(parent, sizer, 1, "Outline");
    colorFill.SetUpColorMenu(parent, sizer, 1, "Fill");
    sizeMenu.SetUpSizeMenu(parent, sizer, "Outline Size");
}

void ShapeToolMenu::ShowMenu(bool show)
{
    shapeMenu.Show(show);
    shapeMenu.SelectShapePane();
    colorOutline.Show(show);
    colorFill.Show(show);
    sizeMenu.Show(show);
}
