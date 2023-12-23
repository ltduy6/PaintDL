#pragma once

#include "../Shape/Shape.h"
#include "../Shape/ShapeUtils.h"
#include "../Transform/Transformation.h"
#include "ObjectSpace.h"

class CanvasObject
{
public:
    CanvasObject(const Shape &shape, Transformation transformation = {}, wxAffineMatrix2D matrix = {});

    void Draw(wxGraphicsContext &gc, bool isExporting = false);
    void SetZoomMatrix(double scaleFactor, wxPoint2DDouble center);

    Transformation GetTransformation() const;
    wxRect2DDouble GetBoundingBox() const;
    Shape &GetShape();
    wxAffineMatrix2D GetTransformationMatrix() const;
    wxAffineMatrix2D GetInverseTransformationMatrix() const;
    wxAffineMatrix2D GetInverseZoomMatrix() const;
    wxString GetName() const;

    bool operator==(const CanvasObject &other) const;
    bool GetCanRotate() const;

    void UpdateScaleFactor(double scaleX, double scaleY);
    void UpdateRotationAngle(double angle);
    void UpdateTranslation(double translationX, double translationY);
    void UpdateZoomMatrix(wxAffineMatrix2D matrix);

    void SetScaleFactor(double scaleX, double scaleY);
    void SetRotationAngle(double angle);
    void SetTranslation(double translationX, double translationY);
    void SetCanRotate(bool canRotate);

    void IncreaseHeight(double height);

private:
    void SetName();

private:
    Shape m_shape;
    wxRect2DDouble m_boundingBox;
    Transformation m_transformation;
    wxString m_name;

    wxAffineMatrix2D m_transformationMatrix;
    wxAffineMatrix2D m_zoomMatrix;

    double initialScaleFactor{1};
    double currentZoomFactor{1};
    bool isCanRotate{true};
    bool isInitialZoom{true};
};