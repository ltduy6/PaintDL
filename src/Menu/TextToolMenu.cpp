#include "TextToolMenu.h"

TextToolMenu::TextToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::Text)
{
    colorMenu.SetUpColorMenu(parent, sizer, 1);
}

void TextToolMenu::ShowMenu(bool show)
{
    colorMenu.Show(show);
}
