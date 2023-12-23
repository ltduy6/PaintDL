#include "ShapePane.h"

ShapePane::ShapePane(wxWindow *parent, wxWindowID id, ShapeType type, const wxPoint &pos, const wxSize &size)
    : SelectablePane(parent, id, pos, size), type(type)
{
    switch (type)
    {
    case ShapeType::Rect:
    {
        bitmap.LoadFile("src/Assets/rectangle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::Circle:
    {
        bitmap.LoadFile("src/Assets/circle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::ITriangle:
    {
        bitmap.LoadFile("src/Assets/ITriangle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::RTriangle:
    {
        bitmap.LoadFile("src/Assets/RTriangle.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ShapeType::Diamond:
    {
        bitmap.LoadFile("src/Assets/diamond.png", wxBITMAP_TYPE_PNG);
        break;
    }
    default:
        break;
    }
}

void ShapePane::DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const
{
    gc->SetPen(*wxTRANSPARENT_PEN);
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);

    if (bitmap.IsOk())
    {
        gc->DrawBitmap(bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
    }
}
