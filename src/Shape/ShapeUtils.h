#pragma once

#include <wx/geometry.h>
#include "Shape.h"
#include "../Helper/Visistor.h"

namespace ShapeUltils
{
    static wxRect2DDouble CalculateBoundingBox(const Shape &shape)
    {
        wxRect2DDouble boundingBox;
        std::visit(Visitor{[&boundingBox](const Rect &rect)
                           {
                               boundingBox = rect.rect;
                           },
                           [&boundingBox](const Circle &circle)
                           {
                               boundingBox = circle.rect;
                           },
                           [&boundingBox](const Path &path)
                           {
                               double minX = std::numeric_limits<double>::max();
                               double minY = std::numeric_limits<double>::max();
                               double maxX = std::numeric_limits<double>::min();
                               double maxY = std::numeric_limits<double>::min();

                               for (const auto &pt : path.points)
                               {
                                   minX = std::min(minX, pt.m_x);
                                   minY = std::min(minY, pt.m_y);
                                   maxX = std::max(maxX, pt.m_x);
                                   maxY = std::max(maxY, pt.m_y);
                               }
                               boundingBox = wxRect2DDouble(minX - path.width / 2, minY - path.width / 2, maxX - minX + path.width, maxY - minY + path.width);
                           }},
                   shape);
        return boundingBox;
    }
}