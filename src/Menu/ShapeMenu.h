#pragma once

#include "ShapePane.h"
#include "../MyApp.h"

#include <functional>

class ShapeMenu
{
public:
    void SetUpShapeMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset);
    void SelectShapePane();
    void AddCallBack(std::function<void()> callBack);

private:
    std::vector<ShapePane *> shapePanes;
    const std::vector<ShapeType> shapeTypes = {ShapeType::Circle, ShapeType::Rect, ShapeType::ITriangle, ShapeType::RTriangle, ShapeType::Diamond};
};