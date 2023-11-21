#pragma once

#include "Transformation.h"
#include <wx/affinematrix2d.h>

namespace TransformWxConversion
{
    wxAffineMatrix2D GetMatrix(Transformation t, wxPoint2DDouble oldScaleCenter, wxPoint2DDouble rotateCenter, wxPoint2DDouble newScaleCenter)
    {
        wxAffineMatrix2D matrix;

        matrix.Translate(t.translationX, t.translationY);

        matrix.Translate(rotateCenter.m_x, rotateCenter.m_y);
        matrix.Rotate(t.rotationAngle);
        matrix.Translate(-rotateCenter.m_x, -rotateCenter.m_y);

        matrix.Translate(newScaleCenter.m_x, newScaleCenter.m_y);
        matrix.Scale(t.scaleX, t.scaleY);
        matrix.Translate(-newScaleCenter.m_x, -newScaleCenter.m_y);

        return matrix;
    }

    wxAffineMatrix2D GetInverseMatrix(Transformation t, wxPoint2DDouble oldScaleCenter, wxPoint2DDouble rotateCenter, wxPoint2DDouble newScaleCenter)
    {
        wxAffineMatrix2D matrix = GetMatrix(t, oldScaleCenter, rotateCenter, newScaleCenter);
        matrix.Invert();

        return matrix;
    }
}