#pragma once

#include "../MyApp.h"
#include "ToolsPane.h"

#include <functional>

class ToolMenu
{
public:
    void SetUpToolMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset);
    void SelectToolPane();

private:
    std::vector<ToolsPane *> toolPanes;
    const std::vector<ToolType> toolTypes = {ToolType::Brush};
};