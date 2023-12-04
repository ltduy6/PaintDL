#include "ImageMenu.h"

void ImageMenu::SetUpImageMenu(wxWindow *parent, wxSizer *sizer)
{
    auto wrapSizer = new wxBoxSizer(wxHORIZONTAL);
    auto label = new wxStaticText(parent, wxID_ANY, "Image");
    label->SetForegroundColour(wxColour(231, 246, 242));

    rotatePane = new ToolsPane(parent, wxID_ANY, ToolType::Rotate);
    wrapSizer->Add(rotatePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));

    sizer->Add(label, 0, wxALL, parent->FromDIP(5));
    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_sizer = wrapSizer;
    m_text = label;
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
