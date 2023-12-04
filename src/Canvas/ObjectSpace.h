#pragma once
class CanvasObject;

namespace ObjectSpace
{
    wxPoint2DDouble ToObjectCoordinates(const CanvasObject &object, wxPoint2DDouble point);
    wxPoint2DDouble ToObjectDistance(const CanvasObject &object, wxPoint2DDouble point);
    wxPoint2DDouble ToScreenCoordinates(const CanvasObject &object, wxPoint2DDouble point);
    wxPoint2DDouble ToScreenDistance(const CanvasObject &object, wxPoint2DDouble point);
    wxPoint2DDouble ReverseScaleCordinates(const CanvasObject &object, wxPoint2DDouble point);
    
    wxAffineMatrix2D GetTransformationMatrix(const CanvasObject &object);
    wxAffineMatrix2D GetInverseTransformationMatrix(const CanvasObject &object);
    wxAffineMatrix2D GetTempTransformationMatrix(const CanvasObject &object);
}