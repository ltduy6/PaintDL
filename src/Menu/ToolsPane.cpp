#include "ToolsPane.h"

ToolsPane::ToolsPane(wxWindow *parent, wxWindowID id, ToolType type, const wxPoint &pos, const wxSize &size)
    : SelectablePane(parent, id, pos, size), m_type(type)
{
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

    switch (m_type)
    {
    case ToolType::Brush:
    {
        wxBitmap bitmap("src/Assets/brush.png", wxBITMAP_TYPE_PNG);
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