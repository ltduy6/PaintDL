#include "ShapeMenu.h"

void ShapeMenu::SetUpShapeMenu(wxWindow *parent, wxSizer *sizer, wxStaticText *text, std::function<void()> reset)
{
    for (const auto &i : shapeTypes)
    {
        auto shapePane = new ShapePane(parent, wxID_ANY, i);

        shapePane->AddCallback([this, i, reset]()
                               { 
                            MyApp::GetStrokeSettings().currentShape = i;
                            MyApp::GetStrokeSettings().currentTool = ToolType::Shape; 
                            reset(); });

        shapePanes.push_back(shapePane);
        sizer->Add(shapePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }
    m_parent = parent;
    m_sizer = sizer;
    m_text = text;
}

void ShapeMenu::SelectShapePane()
{
    for (auto shapePane : shapePanes)
    {
        shapePane->selected = (shapePane->type == MyApp::GetStrokeSettings().currentShape);
        shapePane->Refresh();
    }
}

void ShapeMenu::AddCallBack(std::function<void()> callBack)
{
    for (const auto &shapePane : shapePanes)
        shapePane->AddCallback(callBack);
}
