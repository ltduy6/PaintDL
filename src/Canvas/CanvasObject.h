#pragma once

#include "../Shape/Shape.h"
#include "../Shape/ShapeUtils.h"
#include "../Transform/Transformation.h"
#include "ObjectSpace.h"

class CanvasObject
{
public:
    CanvasObject(const Shape &shape, Transformation transformation = {});

    void Draw(wxGraphicsContext &gc);
    void SetScaleMatrix(double scaleFactor, wxPoint2DDouble center);

    Transformation GetTransformation() const;
    wxRect2DDouble GetBoundingBox() const;
    Shape &GetShape();
    wxPoint2DDouble GetCenter() const;
    wxPoint2DDouble GetOldCenter() const;
    wxAffineMatrix2D GetLastTransformationMatrix() const;

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
    Shape m_shape;
    wxRect2DDouble m_boundingBox;
    Transformation m_transformation;
    wxPoint2DDouble m_center;
    wxPoint2DDouble m_oldCenter;
    wxAffineMatrix2D m_lastTransformationMatrix;
    wxAffineMatrix2D m_scaleMatrix;
    double initialScaleFactor{1};
    bool isCanRotate{true};
};