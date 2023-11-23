#include "ToolMenu.h"

void ToolMenu::SetUpToolMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset)
{
    for (const auto toolType : toolTypes)
    {
        auto toolPane = new ToolsPane(parent, wxID_ANY, toolType);
        toolPane->AddCallback([this, toolType, reset]()
                              { 
                        MyApp::GetStrokeSettings().currentTool = toolType;
                        if(toolType == ToolType::Brush)
                            MyApp::GetStrokeSettings().currentShape = ShapeType::Path;
                        else if(toolType == ToolType::Transform)
                            MyApp::GetStrokeSettings().currentShape = ShapeType::None;
                        else if(toolType == ToolType::Text)
                            MyApp::GetStrokeSettings().currentShape = ShapeType::Text; });
        toolPanes.push_back(toolPane);
        sizer->Add(toolPane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }

    AddCallBack(reset);
    MyApp::GetStrokeSettings().currentTool = ToolType::Brush;
    MyApp::GetStrokeSettings().currentShape = ShapeType::Path;
    reset();
}

void ToolMenu::SelectToolPane()
{
    for (auto toolPane : toolPanes)
    {
        toolPane->selected = (toolPane->getToolType() == MyApp::GetStrokeSettings().currentTool);
        toolPane->Refresh();
    }
}

void ToolMenu::AddCallBack(std::function<void()> callBack)
{
    for (const auto &toolPane : toolPanes)
    {
        toolPane->AddCallback(callBack);
    }
}

void ToolMenu::AddShowCallBack(std::function<void()> callBack, ToolType type)
{
    for (const auto &toolPane : toolPanes)
    {
        if (toolPane->getToolType() == type)
        {
            toolPane->AddCallback(callBack);
            break;
        }
    }
}

void ToolMenu::AddHideCallBack(std::function<void()> callBack, ToolType type)
{
    for (const auto &toolPane : toolPanes)
    {
        if (toolPane->getToolType() == type)
        {
            toolPane->AddCallback(callBack);
            break;
        }
    }
}
