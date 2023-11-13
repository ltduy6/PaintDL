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

    switch (type)
    {
    case ShapeType::Rect:
    {
        wxBitmap bitmap("src/Assets/rectangle.png", wxBITMAP_TYPE_PNG);
        if (bitmap.IsOk())
        {
            gc->DrawBitmap(bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
        }
        break;
    }
    case ShapeType::Circle:
    {
        wxBitmap bitmap("src/Assets/circle.png", wxBITMAP_TYPE_PNG);
        if (bitmap.IsOk())
        {
            gc->DrawBitmap(bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
        }
        break;
    }
    case ShapeType::ITriangle:
    {
        wxBitmap bitmap("src/Assets/ITriangle.png", wxBITMAP_TYPE_PNG);
        if (bitmap.IsOk())
        {
            gc->DrawBitmap(bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
        }
        break;
    }
    case ShapeType::RTriangle:
    {
        wxBitmap bitmap("src/Assets/RTriangle.png", wxBITMAP_TYPE_PNG);
        if (bitmap.IsOk())
        {
            gc->DrawBitmap(bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
        }
        break;
    }
    case ShapeType::Diamond:
    {
        wxBitmap bitmap("src/Assets/diamond.png", wxBITMAP_TYPE_PNG);
        if (bitmap.IsOk())
        {
            gc->DrawBitmap(bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
        }
        break;
    }

    default:
        break;
    }
}
