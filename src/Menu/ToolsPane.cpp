#include "ToolsPane.h"

ToolsPane::ToolsPane(wxWindow *parent, wxWindowID id, ToolType type, const wxPoint &pos, const wxSize &size)
    : SelectablePane(parent, id, pos, size), m_type(type)
{
    switch (m_type)
    {
    case ToolType::Brush:
    {
        m_bitmap.LoadFile("src/Assets/brush.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::Transform:
    {
        m_bitmap.LoadFile("src/Assets/select.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::Rotate:
    {
        m_bitmap.LoadFile("src/Assets/rotate.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::CustomColor:
    {
        m_bitmap.LoadFile("src/Assets/color-wheel.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::Text:
    {
        m_bitmap.LoadFile("src/Assets/text.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::ZoomIn:
    {
        m_bitmap.LoadFile("src/Assets/zoom-in.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::Shape:
    {
        m_bitmap.LoadFile("src/Assets/shapes.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::Move:
    {
        m_bitmap.LoadFile("src/Assets/move.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::Font:
    {
        m_bitmap.LoadFile("src/Assets/font.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::Gradient:
    {
        m_bitmap.LoadFile("src/Assets/gradient.png", wxBITMAP_TYPE_PNG);
        break;
    }
    case ToolType::NoFill:
    {
        m_bitmap.LoadFile("src/Assets/no-fill.png", wxBITMAP_TYPE_PNG);
        break;
    }
    default:
        break;
    }
}

void ToolsPane::setToolType(ToolType type)
{
    m_type = type;
}

ToolType ToolsPane::getToolType() const
{
    return m_type;
}

void ToolsPane::DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const
{
    gc->SetPen(*wxTRANSPARENT_PEN);
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);

    if (m_bitmap.IsOk())
    {
        gc->DrawBitmap(m_bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
    }
}