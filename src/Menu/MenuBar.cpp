#include "MenuBar.h"

void MenuBar::SetUp(wxWindow *parent, wxSizer *sizer, wxWindow *toolsParent, wxSizer *toolsSizer)
{
    for (const auto &type : toolTypes)
    {
        auto toolMenu = GenToolMenu(type, parent, sizer, toolsParent, toolsSizer);
        toolMenu->SetCallback([this, type, toolsParent]()
                              { toolsParent->Refresh();
                                ShowToolMenu(type); });
        toolMenus.push_back(toolMenu);
    }

    ShowToolMenu(ToolType::Brush);
    parent = parent;
}

void MenuBar::SetUpDrawingCanvas(DrawingCanvas *drawingCanvas)
{
    for (auto toolMenu : toolMenus)
    {
        toolMenu->SetCallback([drawingCanvas]()
                              { if(drawingCanvas)
                                    drawingCanvas->ReFreshCanvas(); });
        if (toolMenu->type == ToolType::Transform)
            dynamic_cast<SelectionToolMenu *>(toolMenu)->CallRotate(drawingCanvas);
    }
}

void MenuBar::ClearMenuBarCallback()
{
    for (auto toolMenu : toolMenus)
    {
        toolMenu->PopCallback();
    }
}

MenuBar::~MenuBar()
{
    for (auto toolMenu : toolMenus)
        delete toolMenu;
}

ToolMenu *MenuBar::GenToolMenu(ToolType type, wxWindow *parent, wxSizer *sizer, wxWindow *toolsParent, wxSizer *toolSizer)
{
    switch (type)
    {
    case ToolType::Brush:
        return new BrushToolMenu(parent, sizer, toolsParent, toolSizer);
    case ToolType::Shape:
        return new ShapeToolMenu(parent, sizer, toolsParent, toolSizer);
    case ToolType::Transform:
        return new SelectionToolMenu(parent, sizer, toolsParent, toolSizer);
    case ToolType::Text:
        return new TextToolMenu(parent, sizer, toolsParent, toolSizer);
    case ToolType::ZoomIn:
        return new ZoomToolMenu(parent, sizer, toolsParent, toolSizer);
    default:
        return nullptr;
    }
}

void MenuBar::ShowToolMenu(ToolType type)
{
    for (auto toolMenu : toolMenus)
        toolMenu->Show(toolMenu->type == type);
}
