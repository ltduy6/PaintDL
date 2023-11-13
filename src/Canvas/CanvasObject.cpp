#include "CanvasObject.h"

CanvasObject::CanvasObject(const Shape &shape, Transformation transformation)
    : m_shape(shape), m_transformation(transformation), m_boundingBox{ShapeUltils::CalculateBoundingBox(shape)}
{
}

void CanvasObject::Draw(wxGraphicsContext &gc) const
{
    gc.PushState();

    gc.SetTransform(gc.CreateMatrix(ObjectSpace::GetTransformationMatrix(*this)));
    std::visit(DrawingVisitor{gc}, m_shape);

    gc.PopState();
}

Transformation CanvasObject::GetTransformation() const
{
    return m_transformation;
}

wxRect2DDouble CanvasObject::GetBoundingBox() const
{
    return m_boundingBox;
}

Shape CanvasObject::GetShape() const
{
    return m_shape;
}

bool CanvasObject::operator==(const CanvasObject &other) const
{
    // return m_shape == other.m_shape && m_transformation == other.m_transformation && m_boundingBox == other.m_boundingBox;
    return true;
}

void CanvasObject::UpdateScaleFactor(double scaleX, double scaleY)
{
    m_transformation.scaleX *= scaleX;
    m_transformation.scaleY *= scaleY;
}

void CanvasObject::UpdateRotationAngle(double angle)
{
    m_transformation.rotationAngle += angle;
}

void CanvasObject::UpdateTranslation(double translationX, double translationY)
{
    m_transformation.translationX += translationX;
    m_transformation.translationY += translationY;
}

void CanvasObject::SetScaleFactor(double scaleX, double scaleY)
{
    m_transformation.scaleX = scaleX;
    m_transformation.scaleY = scaleY;
}

void CanvasObject::SetRotationAngle(double angle)
{
    m_transformation.rotationAngle = angle;
}

void CanvasObject::SetTranslation(double translationX, double translationY)
{
    m_transformation.translationX = translationX;
    m_transformation.translationY = translationY;
}
