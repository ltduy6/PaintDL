#include "ShapeMenu.h"

void ShapeMenu::SetUpShapeMenu(wxWindow *parent, wxSizer *sizer, std::function<void()> reset)
{
    for (const auto &i : shapeTypes)
    {
        auto shapePane = new ShapePane(parent, wxID_ANY, i);

        shapePane->Bind(wxEVT_LEFT_DOWN, [this, i, reset](wxMouseEvent &event)
                        { 
                            MyApp::GetStrokeSettings().currentShape = i;
                            MyApp::GetStrokeSettings().currentTool = ToolType::None;
                            reset(); });

        shapePanes.push_back(shapePane);
        sizer->Add(shapePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }
}

void ShapeMenu::SelectShapePane()
{
    for (auto shapePane : shapePanes)
    {
        shapePane->selected = (shapePane->type == MyApp::GetStrokeSettings().currentShape);
        shapePane->Refresh();
    }
}
