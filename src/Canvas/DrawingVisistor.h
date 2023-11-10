#pragma once

#include <wx/graphics.h>
#include <wx/dcclient.h>
#include <wx/wx.h>
#include "Shape/Shape.h"

struct DrawingVisitor
{
    wxGraphicsContext &gc;

    void operator()(const Rect &rect)
    {
        gc.SetPen(wxPen(rect.color, rect.width));
        gc.DrawRectangle(rect.rect.m_x, rect.rect.m_y, rect.rect.m_width, rect.rect.m_height);
    }

    void operator()(const Path &path)
    {
        if (path.points.size() > 1)
        {
            gc.SetPen(wxPen(path.color, path.width));
            gc.StrokeLines(path.points.size(), path.points.data());
        }
    }

    void operator()(const Circle &circle)
    {
        gc.SetPen(wxPen(circle.color, circle.width));
        wxPoint2DDouble center = circle.rect.GetCentre();
        gc.DrawEllipse(center.m_x - circle.rect.m_width / 2.0, center.m_y - circle.rect.m_height / 2.0, circle.rect.m_width, circle.rect.m_height);
    }

    void operator()(const ITriangle &triangle)
    {
        gc.SetPen(wxPen(triangle.color, triangle.width));

        wxPoint2DDouble points[3];
        points[0] = {(triangle.drag.m_x + triangle.origin.m_x) / 2, std::min(triangle.drag.m_y, triangle.origin.m_y)};
        points[1] = {std::min(triangle.drag.m_x, triangle.origin.m_x), std::max(triangle.drag.m_y, triangle.origin.m_y)};
        points[2] = {std::max(triangle.drag.m_x, triangle.origin.m_x), std::max(triangle.drag.m_y, triangle.origin.m_y)};

        wxGraphicsPath path = gc.CreatePath();
        path.MoveToPoint(points[0]);
        path.AddLineToPoint(points[1]);
        path.AddLineToPoint(points[2]);
        path.CloseSubpath();

        gc.FillPath(path);
        gc.StrokePath(path);
    }

    void operator()(const RTriangle &triangle)
    {
        gc.SetPen(wxPen(triangle.color, triangle.width));

        wxPoint2DDouble points[3];
        points[0] = triangle.origin;
        points[1] = triangle.drag;
        points[2] = {std::min(triangle.drag.m_x, triangle.origin.m_x), std::max(triangle.drag.m_y, triangle.origin.m_y)};

        wxGraphicsPath path = gc.CreatePath();
        path.MoveToPoint(points[0]);
        path.AddLineToPoint(points[1]);
        path.AddLineToPoint(points[2]);
        path.CloseSubpath();

        gc.FillPath(path);
        gc.StrokePath(path);
    }

    void operator()(const Diamond &diamond)
    {
        gc.SetPen(wxPen(diamond.color, diamond.width));

        wxPoint2DDouble points[4];
        points[0] = {diamond.rect.m_x + diamond.rect.m_width / 2, diamond.rect.m_y};
        points[1] = {diamond.rect.m_x + diamond.rect.m_width, diamond.rect.m_y + diamond.rect.m_height / 2};
        points[2] = {diamond.rect.m_x + diamond.rect.m_width / 2, diamond.rect.m_y + diamond.rect.m_height};
        points[3] = {diamond.rect.m_x, diamond.rect.m_y + diamond.rect.m_height / 2};

        wxGraphicsPath path = gc.CreatePath();
        path.MoveToPoint(points[0]);
        path.AddLineToPoint(points[1]);
        path.AddLineToPoint(points[2]);
        path.AddLineToPoint(points[3]);
        path.CloseSubpath();

        gc.FillPath(path);
        gc.StrokePath(path);
    }
};