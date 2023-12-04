#include "SelectionToolMenu.h"

SelectionToolMenu::SelectionToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::Transform)
{
    imageMenu.SetUpImageMenu(parent, sizer);
}

void SelectionToolMenu::ShowMenu(bool show)
{
    imageMenu.Show(show);
}
