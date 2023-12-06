#include <wx/affinematrix2d.h>
#include <wx/geometry.h>

#include "ObjectSpace.h"
#include "CanvasObject.h"
#include "../Transform/Conversion.h"

wxPoint2DDouble ObjectSpace::ToObjectCoordinates(const CanvasObject &object, wxPoint2DDouble point)
{
    return GetInverseTransformationMatrix(object).TransformPoint(point);
}

wxPoint2DDouble ObjectSpace::ToObjectDistance(const CanvasObject &object, wxPoint2DDouble point)
{
    return GetInverseTransformationMatrix(object).TransformDistance(point);
}

wxPoint2DDouble ObjectSpace::ToScreenCoordinates(const CanvasObject &object, wxPoint2DDouble point)
{
    return GetTransformationMatrix(object).TransformPoint(point);
}

wxPoint2DDouble ObjectSpace::ToScreenDistance(const CanvasObject &object, wxPoint2DDouble point)
{
    return GetTransformationMatrix(object).TransformDistance(point);
}

wxPoint2DDouble ObjectSpace::InverseZoomDistance(const CanvasObject &object, wxPoint2DDouble point)
{
    return object.GetInverseZoomMatrix().TransformDistance(point);
}

wxAffineMatrix2D ObjectSpace::GetTransformationMatrix(const CanvasObject &object)
{
    return object.GetTransformationMatrix();
}

wxAffineMatrix2D ObjectSpace::GetInverseTransformationMatrix(const CanvasObject &object)
{
    return object.GetInverseTransformationMatrix();
}

wxAffineMatrix2D ObjectSpace::GetTempTransformationMatrix(const CanvasObject &object)
{
    return TransformWxConversion::GetMatrix(object.GetTransformation(), object.GetBoundingBox().GetCentre(), object.GetBoundingBox().GetCentre());
}
