#include "CanvasObject.h"
#include "DrawingVisistor.h"

double CanvasObject::globalScaleFactor = 1;

CanvasObject::CanvasObject(const Shape &shape, Transformation transformation, wxAffineMatrix2D matrix)
    : m_shape(shape), m_transformation(transformation), m_boundingBox{ShapeUltils::CalculateBoundingBox(shape)},
      m_zoomMatrix(matrix), currentZoomFactor(globalScaleFactor)
{
    m_center = m_boundingBox.GetCentre();
    // m_scaleMatrix = matrix;
    // m_scaleMatrix.Invert();
    // GenerateTransformationMatrix();
}

void CanvasObject::Draw(wxGraphicsContext &gc)
{
    gc.PushState();

    gc.SetTransform(gc.CreateMatrix(m_zoomMatrix));
    wxAffineMatrix2D *matrix = new wxAffineMatrix2D(m_transformationMatrix);
    wxDouble *angle = new wxDouble(m_transformation.rotationAngle);
    std::visit(DrawingVisitor{gc, matrix, &m_boundingBox, angle}, m_shape);
    delete matrix;
    delete angle;

    gc.PopState();
}

void CanvasObject::SetZoomMatrix(double scaleFactor, wxPoint2DDouble center)
{
    // center = ObjectSpace::ToObjectCoordinates(*this, center);
    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Translate(center.m_x, center.m_y);
    newMatrix->Scale(scaleFactor, scaleFactor);
    newMatrix->Translate(-center.m_x, -center.m_y);
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

wxPoint2DDouble CanvasObject::GetCenter() const
{
    return m_center;
}

wxPoint2DDouble CanvasObject::GetOldCenter() const
{
    return m_oldCenter;
}

wxAffineMatrix2D CanvasObject::GetTransformationMatrix() const
{
    wxAffineMatrix2D matrix = m_zoomMatrix;
    matrix.Concat(m_transformationMatrix);
    return matrix;
}

wxAffineMatrix2D CanvasObject::GetInverseTransformationMatrix() const
{
    wxAffineMatrix2D matrix = m_zoomMatrix;
    matrix.Concat(m_transformationMatrix);
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

    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();

    newMatrix->Translate(m_center.m_x, m_center.m_y);
    newMatrix->Scale(scaleX, scaleY);
    newMatrix->Translate(-m_center.m_x, -m_center.m_y);

    m_scaleMatrix.Concat(*newMatrix);
    delete newMatrix;

    GenerateTransformationMatrix();
}

void CanvasObject::UpdateRotationAngle(double angle)
{
    m_transformation.rotationAngle += angle;

    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Translate(m_center.m_x, m_center.m_y);
    newMatrix->Rotate(angle);
    newMatrix->Translate(-m_center.m_x, -m_center.m_y);

    newMatrix->Concat(m_rotationMatrix);
    m_rotationMatrix = *newMatrix;
    delete newMatrix;

    GenerateTransformationMatrix();
}

void CanvasObject::UpdateTranslation(double translationX, double translationY)
{
    m_transformation.translationX += translationX;
    m_transformation.translationY += translationY;

    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Translate(translationX / globalScaleFactor, translationY / globalScaleFactor);

    m_translationMatrix.Concat(*newMatrix);
    delete newMatrix;

    GenerateTransformationMatrix();
}

void CanvasObject::UpdateMatrix(wxAffineMatrix2D matrix)
{
    m_transformationMatrix = matrix;
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

void CanvasObject::SetCanRotate(bool canRotate)
{
    isCanRotate = canRotate;
}

void CanvasObject::IncreaseHeight(double height)
{
    m_boundingBox.m_height = height;
}

void CanvasObject::GenerateTransformationMatrix()
{
    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Concat(m_translationMatrix);
    newMatrix->Concat(m_rotationMatrix);
    newMatrix->Concat(m_scaleMatrix);
    m_transformationMatrix = *newMatrix;
    delete newMatrix;
}
