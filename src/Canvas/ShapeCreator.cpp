#include "ShapeCreator.h"

void ShapeCreator::Start(StrokeSettings strokeSettings, wxPoint point)
{
    shape.emplace(ShapeFactory::CreateShape(strokeSettings, point));
    lastDragStart = point;
}

void ShapeCreator::Update(wxPoint pt)
{
    if (!shape)
    {
        throw std::runtime_error("ShapeCreator::Update() called without Start()");
    }

    std::visit(Visitor{[&](Path &path)
                       {
                           path.points.push_back(pt);
                       },
                       [&](Rect &rect)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           rect.rect.SetLeft(left);
                           rect.rect.SetRight(right);
                           rect.rect.SetTop(top);
                           rect.rect.SetBottom(bottom);
                       },
                       [&](Circle &circle)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           circle.rect.SetLeft(left);
                           circle.rect.SetRight(right);
                           circle.rect.SetTop(top);
                           circle.rect.SetBottom(bottom);
                       },
                       [&](ITriangle &triangle)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           triangle.rect.SetLeft(left);
                           triangle.rect.SetRight(right);
                           triangle.rect.SetTop(top);
                           triangle.rect.SetBottom(bottom);
                       },
                       [&](RTriangle &triangle)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           triangle.rect.SetLeft(left);
                           triangle.rect.SetRight(right);
                           triangle.rect.SetTop(top);
                           triangle.rect.SetBottom(bottom);
                       },
                       [&](Diamond &diamond)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           diamond.rect.SetLeft(left);
                           diamond.rect.SetRight(right);
                           diamond.rect.SetTop(top);
                           diamond.rect.SetBottom(bottom);
                       }},
               shape.value());
}

CanvasObject ShapeCreator::FinishAndGenerateObject()
{
    if (!shape)
    {
        throw std::runtime_error("ShapeCreator::FinishAndGenerateObject() called without Start()");
    }
    return CanvasObject{std::exchange(shape, {}).value()};
}

void ShapeCreator::Cancel()
{
    shape = {};
}

bool ShapeCreator::IsCreating() const
{
    return shape.has_value();
}

void ShapeCreator::Draw(wxGraphicsContext &gc)
{
    if (!shape)
    {
        return;
    }

    std::visit(DrawingVisitor{gc}, shape.value());
}
