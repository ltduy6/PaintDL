#include "TextToolMenu.h"

TextToolMenu::TextToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::Text)
{
    fontMenu.SetUpFontMenu(parent, sizer);
}

void TextToolMenu::ShowMenu(bool show)
{
    fontMenu.Show(show);
}
