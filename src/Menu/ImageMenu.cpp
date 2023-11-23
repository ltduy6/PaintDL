#include "ImageMenu.h"

void ImageMenu::SetUpImageMenu(wxWindow *parent, wxSizer *sizer, wxStaticText *text)
{
    rotatePane = new ToolsPane(parent, wxID_ANY, ToolType::Rotate);
    sizer->Add(rotatePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    m_sizer = sizer;
    m_text = text;
    m_parent = parent;
}

void ImageMenu::CallRotate(DrawingCanvas *canvas)
{
    rotatePane->AddCallback([canvas]()
                            { canvas->RotateCommand(); });
}
ToolsPane *ImageMenu::GetRotatePane() const
{
    return rotatePane;
}
