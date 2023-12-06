#pragma once

#include "BrushToolMenu.h"
#include "ShapeToolMenu.h"
#include "SelectionToolMenu.h"
#include "TextToolMenu.h"
#include "ZoomToolMenu.h"
#include "MoveToolMenu.h"
#include "../Canvas/DrawingCanvas.h"

class MenuBar
{
public:
    void SetUp(wxWindow *parent, wxSizer *sizer, wxWindow *toolsParent, wxSizer *toolsSizer);
    void SetUpDrawingCanvas(DrawingCanvas *drawingCanvas);
    void ClearMenuBarCallback();
    ~MenuBar();

private:
    ToolMenu *GenToolMenu(ToolType type, wxWindow *parent, wxSizer *sizer, wxWindow *toolsParent, wxSizer *toolSizer);
    void ShowToolMenu(ToolType type);

private:
    std::vector<ToolMenu *> toolMenus;
    wxWindow *parent;
    const std::vector<ToolType> toolTypes = {ToolType::Brush, ToolType::Shape, ToolType::Transform, ToolType::Text, ToolType::ZoomIn, ToolType::Move};
};