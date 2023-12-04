#include "ShapeMenu.h"

void ShapeMenu::SetUpShapeMenu(wxWindow *parent, wxSizer *sizer)
{
    auto wrapSizer = new wxWrapSizer(wxHORIZONTAL);
    auto label = new wxStaticText(parent, wxID_ANY, "Shape");
    label->SetForegroundColour(wxColour(231, 246, 242));

    for (const auto &i : shapeTypes)
    {
        auto shapePane = new ShapePane(parent, wxID_ANY, i);

        shapePane->AddCallback([this, i]()
                               { 
                            MyApp::GetStrokeSettings().currentShape = i;
                            MyApp::GetStrokeSettings().currentTool = ToolType::Shape;
                            SelectShapePane(); });

        shapePanes.push_back(shapePane);
        wrapSizer->Add(shapePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }

    sizer->Add(label, 0, wxALL, parent->FromDIP(5));
    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_parent = parent;
    m_sizer = wrapSizer;
    m_text = label;
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
