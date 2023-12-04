#include "ToolMenu.h"

ToolMenu::ToolMenu(wxWindow *parent, wxSizer *sizer, ToolType type) : type(type)
{
    mainToolPane = new ToolsPane(parent, wxID_ANY, type);
    mainToolPane->AddCallback([this, type]()
                              { 
                        MyApp::GetStrokeSettings().currentTool = type;
                        if(type == ToolType::Brush)
                            MyApp::GetStrokeSettings().currentShape = ShapeType::Path;
                        else if(type == ToolType::Transform)
                            MyApp::GetStrokeSettings().currentShape = ShapeType::None;
                        else if(type == ToolType::Text)
                            MyApp::GetStrokeSettings().currentShape = ShapeType::Text;
                        else if(type == ToolType::Shape)
                            MyApp::GetStrokeSettings().currentShape = ShapeType::Rect; });
    sizer->Add(mainToolPane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
}

void ToolMenu::Show(bool show)
{
    mainToolPane->selected = show;
    ShowMenu(show);
}

void ToolMenu::SetCallback(std::function<void()> callback)
{
    mainToolPane->AddCallback(callback);
}

void ToolMenu::PopCallback()
{
    mainToolPane->PopCallback();
    ItemPopCallback();
}
