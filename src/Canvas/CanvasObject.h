#pragma once

#include "../Shape/Shape.h"
#include "../Shape/ShapeUtils.h"
#include "../Transform/Transformation.h"
#include "ObjectSpace.h"

class CanvasObject
{
public:
    CanvasObject(const Shape &shape, Transformation transformation = {}, wxAffineMatrix2D matrix = {});

    void Draw(wxGraphicsContext &gc);
    void SetZoomMatrix(double scaleFactor, wxPoint2DDouble center);

    Transformation GetTransformation() const;
    wxRect2DDouble GetBoundingBox() const;
    Shape &GetShape();
    wxPoint2DDouble GetCenter() const;
    wxPoint2DDouble GetOldCenter() const;
    wxAffineMatrix2D GetTransformationMatrix() const;
    wxAffineMatrix2D GetInverseTransformationMatrix() const;

    bool operator==(const CanvasObject &other) const;
    bool GetCanRotate() const;

    void UpdateScaleFactor(double scaleX, double scaleY);
    void UpdateRotationAngle(double angle);
    void UpdateTranslation(double translationX, double translationY);
    void UpdateMatrix(wxAffineMatrix2D matrix);

    void SetScaleFactor(double scaleX, double scaleY);
    void SetRotationAngle(double angle);
    void SetTranslation(double translationX, double translationY);
    void SetCenter(wxPoint2DDouble center);
    void SetCanRotate(bool canRotate);

    void IncreaseHeight(double height);

public:
    static double globalScaleFactor;

private:
    void GenerateTransformationMatrix();

private:
    enum class TransformationType
    {
        Scale,
        Rotate,
        Translate,
        None
    };

private:
    Shape m_shape;
    wxRect2DDouble m_boundingBox;
    Transformation m_transformation;
    wxPoint2DDouble m_center;
    wxPoint2DDouble m_oldCenter;
    wxAffineMatrix2D m_transformationMatrix;
    wxAffineMatrix2D m_scaleMatrix;
    wxAffineMatrix2D m_rotationMatrix;
    wxAffineMatrix2D m_translationMatrix;
    wxAffineMatrix2D m_zoomMatrix;

    TransformationType m_lastTransformationType{TransformationType::None};
    double initialScaleFactor{1};
    double currentZoomFactor{1};
    bool isCanRotate{true};
    bool isInitialZoom{true};
};