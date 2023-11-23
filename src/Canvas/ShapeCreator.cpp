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
                       },
                       [&](Text &text)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           text.rect.SetLeft(left);
                           text.rect.SetRight(right);
                           text.rect.SetTop(top);
                           text.rect.SetBottom(bottom);
                       }},
               shape.value());
}

void ShapeCreator::UpdateKey(wxChar key)
{
    if (!shape)
    {
        throw std::runtime_error("ShapeCreator::Update() called without Start()");
    }
    std::visit(Visitor{[&](Path &path) {
                       },
                       [&](Rect &rect) {
                       },
                       [&](Circle &circle) {
                       },
                       [&](ITriangle &triangle) {
                       },
                       [&](RTriangle &triangle) {
                       },
                       [&](Diamond &diamond) {
                       },
                       [&](Text &text)
                       {
                           text.text += wxChar(key);
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

CanvasObject ShapeCreator::GenerateTextObject()
{
    return CanvasObject{shape.value()};
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

    std::visit(DrawingVisitor{gc, nullptr, nullptr, nullptr}, shape.value());
}
