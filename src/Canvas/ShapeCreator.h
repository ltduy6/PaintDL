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
    void Start(StrokeSettings strokeSettings, wxPoint point);
    void Update(wxPoint pt);
    CanvasObject FinishAndGenerateObject();
    void Cancel();
    bool IsCreating() const;
    void Draw(wxGraphicsContext &gc);

private:
    std::optional<Shape> shape;
    wxPoint lastDragStart;
};