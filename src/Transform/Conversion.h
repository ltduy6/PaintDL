#pragma once

#include "Transformation.h"
#include <wx/affinematrix2d.h>

namespace TransformWxConversion
{
    wxAffineMatrix2D GetMatrix(Transformation t, wxPoint2DDouble scaleCenter, wxPoint2DDouble rotateCenter)
    {
        wxAffineMatrix2D matrix;

        matrix.Translate(t.translationX, t.translationY);

        matrix.Translate(rotateCenter.m_x, rotateCenter.m_y);
        matrix.Rotate(t.rotationAngle);
        matrix.Translate(-rotateCenter.m_x, -rotateCenter.m_y);

        matrix.Translate(scaleCenter.m_x, scaleCenter.m_y);
        matrix.Scale(t.scaleX, t.scaleY);
        matrix.Translate(-scaleCenter.m_x, -scaleCenter.m_y);

        matrix.Concat(t.zoomMatrix);

        return matrix;
    }

    wxAffineMatrix2D GetInverseMatrix(Transformation t, wxPoint2DDouble scaleCenter, wxPoint2DDouble rotateCenter)
    {
        wxAffineMatrix2D matrix = GetMatrix(t, scaleCenter, rotateCenter);
        matrix.Invert();

        return matrix;
    }
}