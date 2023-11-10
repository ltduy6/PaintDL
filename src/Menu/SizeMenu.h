#pragma once

#include "SizePane.h"
#include "../MyApp.h"
#include <vector>

class SizeMenu
{
public:
    void SetUpSizeMenu(wxWindow *parent, wxSizer *sizer);

private:
    void SelectSizePane(SizePane *pane);

private:
    std::vector<SizePane *> sizePanes;
    const std::vector<int> penWidths = {1, 3, 5, 8};
};