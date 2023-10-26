#include "DrawingCanvas.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <iostream>

DrawingCanvas::DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size), penColor(*wxBLACK)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnLeftDown, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnLeftUp, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMotion, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnLeave, this);
    this->Bind(wxEVT_RIGHT_DOWN, &DrawingCanvas::OnEraseBackground, this);
}

void DrawingCanvas::SetPenColor(const wxColour &color)
{
    penColor = color;
}

void DrawingCanvas::SetPenWidth(int width)
{
    penWidth = width;
}

void DrawingCanvas::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        DrawContext(gc);
        delete gc;
    }
}

void DrawingCanvas::OnLeftDown(wxMouseEvent &event)
{
    lines.push_back(Path{penColor, penWidth, {}});
    isDrawing = true;
}

void DrawingCanvas::OnLeftUp(wxMouseEvent &event)
{
    isDrawing = false;
}

void DrawingCanvas::OnMotion(wxMouseEvent &event)
{
    if (isDrawing)
    {
        auto pt = event.GetPosition();
        auto &currentPath = lines.back();

        currentPath.points.push_back(pt);
        Refresh();
    }
}

void DrawingCanvas::OnLeave(wxMouseEvent &event)
{
    isDrawing = false;
}

void DrawingCanvas::OnEraseBackground(wxMouseEvent &event)
{
    if (!lines.empty())
    {
        lines.pop_back();
        Refresh();
    }
}

void DrawingCanvas::DrawContext(wxGraphicsContext *gc)
{
    for (const auto &path : lines)
    {
        auto pointsVector = path.points;
        if (pointsVector.size() > 1)
        {
            wxGraphicsGradientStops stops;
            stops.Add(wxGraphicsGradientStop(*wxRED, 0.5));
            stops.Add(wxGraphicsGradientStop(*wxGREEN, 1.0));
            wxGraphicsBrush brush = gc->CreateLinearGradientBrush(0, 0, 0, path.width, stops);
            gc->SetPen(wxPen(
                path.color,
                path.width));
            gc->SetBrush(brush);
            gc->StrokeLines(pointsVector.size(), pointsVector.data());
        }
    }
}
