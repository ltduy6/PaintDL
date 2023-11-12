#pragma once

#include "../Shape/Shape.h"
#include "../Shape/ShapeUtils.h"
#include "../Transform/Transformation.h"
#include "DrawingVisistor.h"
#include "ObjectSpace.h"

class CanvasObject
{
public:
    CanvasObject(const Shape &shape, Transformation transformation = {});

    void Draw(wxGraphicsContext &gc) const;

    Transformation GetTransformation() const;
    wxRect2DDouble GetBoundingBox() const;
    Shape GetShape() const;

    void UpdateScaleFactor(double scaleX, double scaleY);
    void UpdateRotationAngle(double angle);
    void UpdateTranslation(double translationX, double translationY);

private:
    const Shape m_shape;
    const wxRect2DDouble m_boundingBox;
    Transformation m_transformation;
};