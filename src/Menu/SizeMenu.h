#pragma once

#include "SizePane.h"
#include "../MyApp.h"
#include "MenuTemplate.h"
#include <vector>

class SizeMenu : public MenuTemplate
{
public:
    void SetUpSizeMenu(wxWindow *parent, wxSizer *sizer, wxStaticText *text);

private:
    void SelectSizePane(SizePane *pane);

private:
    std::vector<SizePane *> sizePanes;
    const std::vector<int> penWidths = {1, 3, 5, 8};
};