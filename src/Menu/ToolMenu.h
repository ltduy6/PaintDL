#pragma once

#include "../MyApp.h"
#include "ToolsPane.h"

#include <functional>

class ToolMenu
{
public:
    void SetUpToolMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset);
    void SelectToolPane();
    void AddCallBack(std::function<void()> callBack);
    void AddShowCallBack(std::function<void()> callBack, ToolType type);
    void AddHideCallBack(std::function<void()> callBack, ToolType type);

private:
    std::vector<ToolsPane *> toolPanes;
    std::vector<std::function<void()>> callBacks;
    const std::vector<ToolType> toolTypes = {ToolType::Brush, ToolType::Transform, ToolType::Text};
};