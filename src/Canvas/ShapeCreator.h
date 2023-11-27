#pragma once

#include <optional>

#include <wx/wx.h>

#include "CanvasObject.h"
#include "../StrokeSettings.h"
#include "../Shape/ShapeFactory.h"
#include "../Helper/Visistor.h"
#include "DrawingVisistor.h"

class ShapeCreator
{
public:
    void Start(StrokeSettings strokeSettings, wxPoint2DDouble point);
    void Update(wxPoint2DDouble pt);
    void UpdateKey(wxChar key);
    CanvasObject FinishAndGenerateObject();
    CanvasObject GenerateTextObject();
    void Cancel();
    bool IsCreating() const;
    void Draw(wxGraphicsContext &gc);
    void SetUpZoomMatrix(double scaleFactor, wxPoint2DDouble center);

private:
    std::optional<Shape> shape;
    wxPoint2DDouble lastDragStart;
    wxAffineMatrix2D m_zoomMatrix;
    double currentZoomFactor{1};
};