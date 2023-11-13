#include "ImageMenu.h"

void ImageMenu::SetUpImageMenu(wxWindow *parent, wxSizer *sizer)
{
    rotatePane = new ToolsPane(parent, wxID_ANY, ToolType::Rotate);
    sizer->Add(rotatePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
}

void ImageMenu::CallRotate(DrawingCanvas *canvas)
{
    rotatePane->AddCallback([canvas]()
                            { canvas->GetView()->PredefinedRotate(M_PI / 2); 
                       canvas->Refresh(); });
}

ToolsPane *ImageMenu::GetRotatePane() const
{
    return rotatePane;
}
