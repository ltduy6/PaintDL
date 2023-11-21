#include "CanvasObject.h"
#include "DrawingVisistor.h"

CanvasObject::CanvasObject(const Shape &shape, Transformation transformation)
    : m_shape(shape), m_transformation(transformation), m_boundingBox{ShapeUltils::CalculateBoundingBox(shape)}
{
    m_center = m_boundingBox.GetCentre();
}

void CanvasObject::Draw(wxGraphicsContext &gc)
{
    gc.PushState();

    wxAffineMatrix2D *matrix = new wxAffineMatrix2D(ObjectSpace::GetTransformationMatrix(*this));
    std::visit(DrawingVisitor{gc, matrix, &m_boundingBox}, m_shape);
    delete matrix;

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

Shape &CanvasObject::GetShape()
{
    return m_shape;
}

wxPoint2DDouble CanvasObject::GetCenter() const
{
    return m_center;
}

wxPoint2DDouble CanvasObject::GetOldCenter() const
{
    return m_oldCenter;
}

wxAffineMatrix2D CanvasObject::GetLastTransformationMatrix() const
{
    return m_lastTransformationMatrix;
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

void CanvasObject::UpdateMatrix(wxAffineMatrix2D matrix)
{
    m_lastTransformationMatrix = matrix;
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

void CanvasObject::SetCenter(wxPoint2DDouble center)
{
    m_oldCenter = m_center;
    m_center = center;
}

void CanvasObject::IncreaseHeight(double height)
{
    m_boundingBox.m_height = height;
}
