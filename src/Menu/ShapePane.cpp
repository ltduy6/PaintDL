#include "ShapePane.h"

ShapePane::ShapePane(wxWindow *parent, wxWindowID id, ShapeType type, const wxPoint &pos, const wxSize &size)
    : SelectablePane(parent, id, pos, size), type(type)
{
}

void ShapePane::DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const
{
    gc->SetPen(*wxTRANSPARENT_PEN);
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);

    wxBitmap *bitmap = nullptr;
    switch (type)
    {
    case ShapeType::Rect:
    {
        bitmap = new wxBitmap("src/Assets/rectangle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::Circle:
    {
        bitmap = new wxBitmap("src/Assets/circle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::ITriangle:
    {
        bitmap = new wxBitmap("src/Assets/ITriangle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::RTriangle:
    {
        bitmap = new wxBitmap("src/Assets/RTriangle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::Diamond:
    {
        bitmap = new wxBitmap("src/Assets/diamond.png", wxBITMAP_TYPE_PNG);
        break;
    }
    default:
        break;
    }
    if (bitmap->IsOk())
    {
        if (!IsEnabled())
        {
            // make the bitmap look disabled
            std::cout << "disabled" << std::endl;
            wxImage image = bitmap->ConvertToImage();
            image = image.ConvertToGreyscale();
            image.SetMaskColour(8, 9, 10);
            image.SetMask(true);
            *bitmap = wxBitmap(image);
        }
        gc->DrawBitmap(*bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
    }
    delete bitmap;
}
