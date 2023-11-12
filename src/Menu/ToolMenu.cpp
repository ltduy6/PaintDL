#include "ToolMenu.h"

void ToolMenu::SetUpToolMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset)
{
    for (const auto toolType : toolTypes)
    {
        auto toolPane = new ToolsPane(parent, wxID_ANY, toolType);
        toolPane->Bind(wxEVT_LEFT_DOWN, [this, toolType, reset](wxMouseEvent &event)
                       { 
                        MyApp::GetStrokeSettings().currentTool = toolType;
                        if(toolType == ToolType::Brush)
                            MyApp::GetStrokeSettings().currentShape = ToolType::Path;
                        else if(toolType == ToolType::Transform)
                            MyApp::GetStrokeSettings().currentShape = ToolType::None;
                        for(const auto& callBack : callBacks)
                            callBack(); });
        toolPanes.push_back(toolPane);
        sizer->Add(toolPane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }

    AddCallBack(reset);
    MyApp::GetStrokeSettings().currentTool = ToolType::Brush;
    MyApp::GetStrokeSettings().currentShape = ToolType::Path;
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
    callBacks.push_back(callBack);
}
