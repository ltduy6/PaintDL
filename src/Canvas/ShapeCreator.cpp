#include "ShapeCreator.h"
#include "CanvasObject.h"

void ShapeCreator::Start(StrokeSettings strokeSettings, wxPoint2DDouble point)
{
    wxAffineMatrix2D *matrix = new wxAffineMatrix2D(m_zoomMatrix);
    matrix->Invert();
    point = matrix->TransformPoint(point);
    shape.emplace(ShapeFactory::CreateShape(strokeSettings, point));
    lastDragStart = point;
    delete matrix;
}

void ShapeCreator::Update(wxPoint2DDouble pt)
{
    if (!shape)
    {
        throw std::runtime_error("ShapeCreator::Update() called without Start()");
    }

    wxAffineMatrix2D *matrix = new wxAffineMatrix2D(m_zoomMatrix);
    matrix->Invert();
    pt = matrix->TransformPoint(pt);
    std::visit(Visitor{[&](Path &path)
                       {
                           path.points.push_back(pt);
                       },
                       [&](Rect &rect)
                       {
                           auto left = std::min(lastDragStart.m_x, pt.m_x);
                           auto right = std::max(lastDragStart.m_x, pt.m_x);
                           auto top = std::min(lastDragStart.m_y, pt.m_y);
                           auto bottom = std::max(lastDragStart.m_y, pt.m_y);

                           rect.rect.SetLeft(left);
                           rect.rect.SetRight(right);
                           rect.rect.SetTop(top);
                           rect.rect.SetBottom(bottom);
                       },
                       [&](Circle &circle)
                       {
                           auto left = std::min(lastDragStart.m_x, pt.m_x);
                           auto right = std::max(lastDragStart.m_x, pt.m_x);
                           auto top = std::min(lastDragStart.m_y, pt.m_y);
                           auto bottom = std::max(lastDragStart.m_y, pt.m_y);

                           circle.rect.SetLeft(left);
                           circle.rect.SetRight(right);
                           circle.rect.SetTop(top);
                           circle.rect.SetBottom(bottom);
                       },
                       [&](ITriangle &triangle)
                       {
                           auto left = std::min(lastDragStart.m_x, pt.m_x);
                           auto right = std::max(lastDragStart.m_x, pt.m_x);
                           auto top = std::min(lastDragStart.m_y, pt.m_y);
                           auto bottom = std::max(lastDragStart.m_y, pt.m_y);

                           triangle.rect.SetLeft(left);
                           triangle.rect.SetRight(right);
                           triangle.rect.SetTop(top);
                           triangle.rect.SetBottom(bottom);
                       },
                       [&](RTriangle &triangle)
                       {
                           auto left = std::min(lastDragStart.m_x, pt.m_x);
                           auto right = std::max(lastDragStart.m_x, pt.m_x);
                           auto top = std::min(lastDragStart.m_y, pt.m_y);
                           auto bottom = std::max(lastDragStart.m_y, pt.m_y);

                           triangle.rect.SetLeft(left);
                           triangle.rect.SetRight(right);
                           triangle.rect.SetTop(top);
                           triangle.rect.SetBottom(bottom);
                       },
                       [&](Diamond &diamond)
                       {
                           auto left = std::min(lastDragStart.m_x, pt.m_x);
                           auto right = std::max(lastDragStart.m_x, pt.m_x);
                           auto top = std::min(lastDragStart.m_y, pt.m_y);
                           auto bottom = std::max(lastDragStart.m_y, pt.m_y);

                           diamond.rect.SetLeft(left);
                           diamond.rect.SetRight(right);
                           diamond.rect.SetTop(top);
                           diamond.rect.SetBottom(bottom);
                       },
                       [&](Text &text)
                       {
                           auto left = std::min(lastDragStart.m_x, pt.m_x);
                           auto right = std::max(lastDragStart.m_x, pt.m_x);
                           auto top = std::min(lastDragStart.m_y, pt.m_y);
                           auto bottom = std::max(lastDragStart.m_y, pt.m_y);

                           text.rect.SetLeft(left);
                           text.rect.SetRight(right);
                           text.rect.SetTop(top);
                           text.rect.SetBottom(bottom);
                       }},
               shape.value());

    delete matrix;
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
    return CanvasObject{std::exchange(shape, {}).value(), {}, m_zoomMatrix};
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
    gc.PushState();
    gc.SetTransform(gc.CreateMatrix(m_zoomMatrix));
    wxAffineMatrix2D *matrix = new wxAffineMatrix2D();
    std::visit(DrawingVisitor{gc, matrix, nullptr}, shape.value());
    delete matrix;
    gc.PopState();
}

void ShapeCreator::SetUpZoomMatrix(double scaleFactor, wxPoint2DDouble center)
{
    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Translate(center.m_x, center.m_y);
    newMatrix->Scale(scaleFactor, scaleFactor);
    newMatrix->Translate(-center.m_x, -center.m_y);
    newMatrix->Concat(m_zoomMatrix);
    m_zoomMatrix = *newMatrix;
    delete newMatrix;
}

void ShapeCreator::UpdateZoomMatrix(wxAffineMatrix2D matrix)
{
    m_zoomMatrix = matrix;
}
