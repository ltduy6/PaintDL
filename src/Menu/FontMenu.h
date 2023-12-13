#pragma once

#include <wx/fontdlg.h>
#include "MenuTemplate.h"
#include "ToolsPane.h"
#include "../MyApp.h"

class FontMenu : public MenuTemplate
{
public:
    void SetUpFontMenu(wxWindow *parent, wxSizer *sizer);

private:
    void SelectFont(wxWindow *parent);
};