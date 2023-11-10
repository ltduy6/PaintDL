#pragma once

#include "ShapePane.h"
#include "../MyApp.h"

#include <functional>

class ShapeMenu
{
public:
    void SetUpShapeMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset);
    void SelectShapePane();

private:
    std::vector<ShapePane *> shapePanes;
    const std::vector<ToolType> shapeTypes = {ToolType::Circle, ToolType::Rect, ToolType::ITriangle, ToolType::RTriangle, ToolType::Diamond};
};