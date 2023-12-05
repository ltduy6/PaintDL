#pragma once

#include <wx/graphics.h>
#include <wx/dcclient.h>
#include <wx/wx.h>
#include "../Shape/Circle.h"
#include "../Shape/Diamond.h"
#include "../Shape/ITriangle.h"
#include "../Shape/Path.h"
#include "../Shape/Rect.h"
#include "../Shape/RTriangle.h"
#include "CanvasObject.h"

struct DrawingVisitor
{
    wxGraphicsContext &gc;
    wxAffineMatrix2D *matrix;
    CanvasObject *m_object;

    void operator()(const Rect &rect)
    {
        gc.SetPen(wxPen(rect.outlineColor, rect.width));
        gc.SetBrush(wxColour(rect.fillColor));

        wxPoint2DDouble *points = new wxPoint2DDouble[5];
        points[0] = rect.rect.GetLeftTop();
        points[1] = rect.rect.GetRightTop();
        points[2] = rect.rect.GetRightBottom();
        points[3] = rect.rect.GetLeftBottom();
        points[4] = rect.rect.GetLeftTop();
        if (matrix)
        {
            for (int i = 0; i < 5; i++)
            {
                points[i] = matrix->TransformPoint(points[i]);
            }
        }
        wxGraphicsPath *path = new wxGraphicsPath(gc.CreatePath());
        for (int i = 0; i < 5; ++i)
        {
            if (i == 0)
                path->MoveToPoint(points[i]);
            else
                path->AddLineToPoint(points[i]);
        }
        path->CloseSubpath();

        gc.FillPath(*path);
        gc.StrokePath(*path);

        delete path;
        delete[] points;
    }

    void operator()(const Path &path)
    {
        if (path.points.size() > 1)
        {
            gc.SetPen(wxPen(path.color, path.width));
            int n = path.points.size();
            wxPoint2DDouble *points = new wxPoint2DDouble[n];
            for (int i = 0; i < path.points.size(); i++)
            {
                points[i] = matrix->TransformPoint(path.points[i]);
            }
            gc.StrokeLines(path.points.size(), points);
            delete[] points;
        }
    }

    void operator()(const Circle &circle)
    {
        // get 500 points in an ellipse
        gc.SetPen(wxPen(circle.outlineColor, circle.width));
        gc.SetBrush(wxColour(circle.fillColor));

        wxPoint2DDouble *points = new wxPoint2DDouble[501];
        for (int i = 0; i < 500; i++)
        {
            points[i] = {circle.rect.m_x + circle.rect.m_width / 2 + circle.rect.m_width / 2 * cos(2.0 * M_PI * i / 500),
                         circle.rect.m_y + circle.rect.m_height / 2 + circle.rect.m_height / 2 * sin(2.0 * M_PI * i / 500)};
        }
        points[500] = points[0];

        if (matrix)
        {
            for (int i = 0; i < 501; i++)
            {
                points[i] = matrix->TransformPoint(points[i]);
            }
        }

        wxGraphicsPath *path = new wxGraphicsPath(gc.CreatePath());
        for (int i = 0; i < 501; ++i)
        {
            if (i == 0)
                path->MoveToPoint(points[i]);
            else
                path->AddLineToPoint(points[i]);
        }
        path->CloseSubpath();

        gc.FillPath(*path);
        gc.StrokePath(*path);

        delete path;
        delete[] points;
    }

    void operator()(const ITriangle &triangle)
    {
        gc.SetPen(wxPen(triangle.outlineColor, triangle.width));
        gc.SetBrush(wxColour(triangle.fillColor));

        wxPoint2DDouble *points = new wxPoint2DDouble[4];
        points[0] = {triangle.rect.GetCentre().m_x, triangle.rect.GetTop()};
        points[1] = triangle.rect.GetLeftBottom();
        points[2] = triangle.rect.GetRightBottom();
        points[3] = points[0];

        if (matrix)
        {
            for (int i = 0; i < 4; i++)
            {
                points[i] = matrix->TransformPoint(points[i]);
            }
        }

        wxGraphicsPath *path = new wxGraphicsPath(gc.CreatePath());
        for (int i = 0; i < 4; ++i)
        {
            if (i == 0)
                path->MoveToPoint(points[i]);
            else
                path->AddLineToPoint(points[i]);
        }
        path->CloseSubpath();

        gc.FillPath(*path);
        gc.StrokePath(*path);

        delete path;
        delete[] points;
    }

    void operator()(const RTriangle &triangle)
    {
        gc.SetPen(wxPen(triangle.outlineColor, triangle.width));
        gc.SetBrush(wxColour(triangle.fillColor));

        wxPoint2DDouble *points = new wxPoint2DDouble[4];
        points[0] = triangle.rect.GetLeftTop();
        points[1] = triangle.rect.GetLeftBottom();
        points[2] = triangle.rect.GetRightBottom();
        points[3] = points[0];

        if (matrix)
        {
            for (int i = 0; i < 4; i++)
            {
                points[i] = matrix->TransformPoint(points[i]);
            }
        }

        wxGraphicsPath *path = new wxGraphicsPath(gc.CreatePath());
        for (int i = 0; i < 4; ++i)
        {
            if (i == 0)
                path->MoveToPoint(points[i]);
            else
                path->AddLineToPoint(points[i]);
        }
        path->CloseSubpath();

        gc.FillPath(*path);
        gc.StrokePath(*path);

        delete path;
        delete[] points;
    }

    void operator()(const Diamond &diamond)
    {
        gc.SetPen(wxPen(diamond.outlineColor, diamond.width));
        gc.SetBrush(wxColour(diamond.fillColor));

        wxPoint2DDouble *points = new wxPoint2DDouble[5];
        points[0] = {diamond.rect.m_x + diamond.rect.m_width / 2, diamond.rect.m_y};
        points[1] = {diamond.rect.m_x + diamond.rect.m_width, diamond.rect.m_y + diamond.rect.m_height / 2};
        points[2] = {diamond.rect.m_x + diamond.rect.m_width / 2, diamond.rect.m_y + diamond.rect.m_height};
        points[3] = {diamond.rect.m_x, diamond.rect.m_y + diamond.rect.m_height / 2};
        points[4] = points[0];

        if (matrix)
        {
            for (int i = 0; i < 5; i++)
            {
                points[i] = matrix->TransformPoint(points[i]);
            }
        }

        wxGraphicsPath *path = new wxGraphicsPath(gc.CreatePath());
        for (int i = 0; i < 5; ++i)
        {
            if (i == 0)
                path->MoveToPoint(points[i]);
            else
                path->AddLineToPoint(points[i]);
        }
        path->CloseSubpath();

        gc.FillPath(*path);
        gc.StrokePath(*path);

        delete path;
        delete[] points;
    }

    void operator()(const Text &text)
    {
        wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
        wxDouble width, height;
        wxDouble *widthBox = new wxDouble(text.rect.m_width);
        wxPoint2DDouble *topLeft = new wxPoint2DDouble(text.rect.m_x, text.rect.m_y);

        gc.SetFont(font, text.color);
        gc.GetTextExtent(text.text, &width, &height);
        gc.PushState();

        if (matrix)
        {
            *widthBox = abs(matrix->TransformDistance(text.rect.GetLeftTop() - text.rect.GetRightTop()).m_x);
            *topLeft = matrix->TransformPoint(text.rect.GetLeftTop());
        }

        wxArrayString lines;
        wxString line = "";
        for (const auto &c : text.text)
        {
            if (c == '\n')
            {
                lines.push_back(line);
                line = "";
            }
            else
            {
                gc.GetTextExtent(line + c, &width, &height);
                if (width < *widthBox)
                {
                    line += c;
                }
                else
                {
                    lines.push_back(line);
                    line = c;
                }
            }
        }
        lines.push_back(line);
        wxDouble *newHeight = new wxDouble(0);
        for (int i = 0; i < lines.size(); i++)
        {
            gc.DrawText(_(lines[i]), topLeft->m_x, topLeft->m_y + i * (height));
            *newHeight += height;
        }
        if (m_object && matrix->TransformDistance({0, text.rect.m_height}).m_y < *newHeight)
        {
            matrix->Invert();
            *newHeight = matrix->TransformDistance({0, *newHeight}).m_y;
            matrix->Invert();
            m_object->IncreaseHeight(*newHeight);
        }
        delete newHeight;
        gc.PopState();
        delete widthBox;
        delete topLeft;
    }
};