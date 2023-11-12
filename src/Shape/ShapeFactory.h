#pragma once

#include <stdexcept>
#include "Shape.h"
#include "../StrokeSettings.h"

struct ShapeFactory
{
    static Shape CreateShape(const StrokeSettings &settings, wxPoint origin)
    {
        wxPoint2DDouble origin2D{origin};
        switch (settings.currentShape)
        {
        case ToolType::Path:
            return Path{settings.color, settings.width, {origin2D}};
        case ToolType::Rect:
            return Rect{{origin2D.m_x, origin2D.m_y, 0, 0}, settings.color, settings.width};
        case ToolType::Circle:
            return Circle{{origin2D.m_x, origin2D.m_y, 0, 0}, settings.color, settings.width};
        case ToolType::ITriangle:
            return ITriangle{{origin2D.m_x, origin2D.m_y, 0, 0}, origin2D, origin2D, settings.color, settings.width};
        case ToolType::RTriangle:
            return RTriangle{{origin2D.m_x, origin2D.m_y, 0, 0}, origin2D, origin2D, settings.color, settings.width};
        case ToolType::Diamond:
            return Diamond{{origin2D.m_x, origin2D.m_y, 0, 0}, settings.color, settings.width};
        default:
            throw std::runtime_error("Unknown shape type");
        }
    }
};
