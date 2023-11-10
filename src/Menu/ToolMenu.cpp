#include "ToolMenu.h"

void ToolMenu::SetUpToolMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset)
{
    for (const auto toolType : toolTypes)
    {
        auto toolPane = new ToolsPane(parent, wxID_ANY, toolType);
        toolPane->Bind(wxEVT_LEFT_DOWN, [this, toolType, reset](wxMouseEvent &event)
                       { 
                        MyApp::GetStrokeSettings().currentTool = toolType;
                        MyApp::GetStrokeSettings().currentShape = ToolType::Path;
                        reset(); });
        toolPanes.push_back(toolPane);
        sizer->Add(toolPane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }

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
