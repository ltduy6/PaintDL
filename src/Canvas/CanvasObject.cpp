#include "CanvasObject.h"
#include "DrawingVisistor.h"

CanvasObject::CanvasObject(const Shape &shape, Transformation transformation, wxAffineMatrix2D matrix)
    : m_shape(shape), m_transformation(transformation), m_boundingBox{ShapeUltils::CalculateBoundingBox(shape)},
      m_zoomMatrix(matrix)
{
}

void CanvasObject::Draw(wxGraphicsContext &gc, bool isExporting)
{
    gc.PushState();

    if (!isExporting)
    {
        gc.SetTransform(gc.CreateMatrix(m_zoomMatrix));
    }

    wxAffineMatrix2D *matrix = new wxAffineMatrix2D(m_transformationMatrix);
    std::visit(DrawingVisitor{gc, matrix, this}, m_shape);
    delete matrix;

    gc.PopState();
}

void CanvasObject::SetZoomMatrix(double scaleFactor, wxPoint2DDouble center)
{
    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Translate(center.m_x, center.m_y);
    newMatrix->Scale(scaleFactor, scaleFactor);
    newMatrix->Translate(-center.m_x, -center.m_y);
    newMatrix->Concat(m_zoomMatrix);
    m_zoomMatrix = *newMatrix;
    delete newMatrix;
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

wxAffineMatrix2D CanvasObject::GetTransformationMatrix() const
{
    wxAffineMatrix2D matrix = m_zoomMatrix;
    matrix.Concat(m_transformationMatrix);
    return matrix;
}

wxAffineMatrix2D CanvasObject::GetInverseTransformationMatrix() const
{
    wxAffineMatrix2D matrix = GetTransformationMatrix();
    matrix.Invert();
    return matrix;
}

wxAffineMatrix2D CanvasObject::GetInverseZoomMatrix() const
{
    wxAffineMatrix2D matrix = m_zoomMatrix;
    matrix.Invert();
    return matrix;
}

bool CanvasObject::operator==(const CanvasObject &other) const
{
    // return m_shape == other.m_shape && m_transformation == other.m_transformation && m_boundingBox == other.m_boundingBox;
    return true;
}

bool CanvasObject::GetCanRotate() const
{
    return isCanRotate;
}

void CanvasObject::UpdateScaleFactor(double scaleX, double scaleY)
{
    m_transformation.scaleX *= scaleX;
    m_transformation.scaleY *= scaleY;

    m_transformationMatrix = ObjectSpace::GetTempTransformationMatrix(*this);
}

void CanvasObject::UpdateRotationAngle(double angle)
{
    m_transformation.rotationAngle += angle;
    m_transformationMatrix = ObjectSpace::GetTempTransformationMatrix(*this);
}

void CanvasObject::UpdateTranslation(double translationX, double translationY)
{
    m_transformation.translationX += translationX;
    m_transformation.translationY += translationY;
    m_transformationMatrix = ObjectSpace::GetTempTransformationMatrix(*this);
}

void CanvasObject::UpdateZoomMatrix(wxAffineMatrix2D matrix)
{
    m_zoomMatrix = matrix;
}

void CanvasObject::SetScaleFactor(double scaleX, double scaleY)
{
    m_transformation.scaleX = scaleX;
    m_transformation.scaleY = scaleY;

    m_transformationMatrix = ObjectSpace::GetTempTransformationMatrix(*this);
}

void CanvasObject::SetRotationAngle(double angle)
{
    m_transformation.rotationAngle = angle;

    m_transformationMatrix = ObjectSpace::GetTempTransformationMatrix(*this);
}

void CanvasObject::SetTranslation(double translationX, double translationY)
{
    m_transformation.translationX = translationX;
    m_transformation.translationY = translationY;

    m_transformationMatrix = ObjectSpace::GetTempTransformationMatrix(*this);
}
void CanvasObject::SetCanRotate(bool canRotate)
{
    isCanRotate = canRotate;
}

void CanvasObject::IncreaseHeight(double height)
{
    std::cout << height / m_boundingBox.m_height << std::endl;
    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    wxPoint2DDouble *center = new wxPoint2DDouble((m_boundingBox.GetLeftTop() + m_boundingBox.GetRightTop()) / 2);
    newMatrix->Translate(center->m_x, center->m_y);
    newMatrix->Scale(1, height / m_boundingBox.m_height);
    newMatrix->Translate(-center->m_x, -center->m_y);
    m_transformationMatrix.Concat(*newMatrix);
    delete newMatrix;
    delete center;
}
