#include "ImageMenu.h"

void ImageMenu::SetUpImageMenu(wxWindow *parent, wxSizer *sizer)
{
    rotatePane = new RoundedButton(parent, wxID_ANY, "rotate.png", wxSize(70, 70));
    sizer->Add(rotatePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
}

void ImageMenu::CallRotate(DrawingCanvas *canvas)
{
    rotatePane->Bind(wxEVT_LEFT_DOWN, [canvas](wxMouseEvent &event)
                     { canvas->GetView()->PredefinedRotate(M_PI / 2); 
                     canvas->Refresh(); });
}

wxButton *ImageMenu::GetRotatePane() const
{
    return rotatePane;
}
