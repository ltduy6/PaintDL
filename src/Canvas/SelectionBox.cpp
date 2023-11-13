#include "SelectionBox.h"

#include <array>

SelectionBox::SelectionBox(CanvasObject &object, double handleWidth) : m_object(object), m_handleWidth(handleWidth)
{
    m_oldTransformation = m_object.get().GetTransformation();
}

Transformation SelectionBox::GetTransformation() const
{
    return m_oldTransformation;
}

CanvasObject &SelectionBox::GetObject() const
{
    // TODO: insert return statement here
    return m_object;
}

void SelectionBox::Draw(wxGraphicsContext &gc) const
{
    gc.PushState();

    gc.SetTransform(gc.CreateMatrix());

    gc.SetPen(wxPen(wxColour(128, 128, 128), 3, wxPENSTYLE_LONG_DASH));
    gc.SetBrush(*wxTRANSPARENT_BRUSH);

    auto rectVertices = std::array{
        GetTopLeftHandleCenter(),
        GetTopRightHandleCenter(),
        GetBottomRightHandleCenter(),
        GetBottomLeftHandleCenter(),
        GetTopLeftHandleCenter(),
    };

    auto rotationHandleStart = GetRotationHandleStart();
    auto rotationHandleCenter = GetRotationHandleCenter();

    gc.StrokeLines(rectVertices.size(), rectVertices.data());
    gc.StrokeLine(rotationHandleStart.m_x, rotationHandleStart.m_y, rotationHandleCenter.m_x, rotationHandleCenter.m_y);

    auto handleCenters = std::array{
        GetTopLeftHandleCenter(),
        GetTopRightHandleCenter(),
        GetBottomLeftHandleCenter(),
        GetBottomRightHandleCenter(),
        GetRotationHandleCenter(),
    };

    for (const auto &center : handleCenters)
    {
        DrawHandle(gc, center);
    }

    gc.PopState();
}

void SelectionBox::StartDragging(wxPoint2DDouble point)
{
    if (HandleHitTest(point, GetRotationHandleCenter()))
    {
        m_draggableElement = DraggableElement::Rotation;
    }
    else if (HandleHitTest(point, GetTopLeftHandleCenter()))
    {
        m_draggableElement = DraggableElement::TopLeft;
    }
    else if (HandleHitTest(point, GetTopRightHandleCenter()))
    {
        m_draggableElement = DraggableElement::TopRight;
    }
    else if (HandleHitTest(point, GetBottomLeftHandleCenter()))
    {
        m_draggableElement = DraggableElement::BottomLeft;
    }
    else if (HandleHitTest(point, GetBottomRightHandleCenter()))
    {
        m_draggableElement = DraggableElement::BottomRight;
    }
    else if (FullBoxHitTest(point))
    {
        m_draggableElement = DraggableElement::FullBox;
    }
    else
    {
        m_draggableElement = {};
    }

    m_lastDragPoint = point;
}

bool SelectionBox::isDragging() const
{
    return m_draggableElement.has_value();
}

void SelectionBox::Drag(wxPoint2DDouble pt)
{
    if (!isDragging())
    {
        throw std::runtime_error("Drag called without StartDragClick");
    }

    switch (m_draggableElement.value())
    {
    case DraggableElement::TopLeft:
        ScaleUsingHandleMovement(m_lastDragPoint, pt, GetTopLeftHandleCenter());
        break;
    case DraggableElement::TopRight:
        ScaleUsingHandleMovement(m_lastDragPoint, pt, GetTopRightHandleCenter());
        break;
    case DraggableElement::BottomLeft:
        ScaleUsingHandleMovement(m_lastDragPoint, pt, GetBottomLeftHandleCenter());
        break;
    case DraggableElement::BottomRight:
        ScaleUsingHandleMovement(m_lastDragPoint, pt, GetBottomRightHandleCenter());
        break;
    case DraggableElement::Rotation:
        RotateUsingHandleMovement(m_lastDragPoint, pt);
        break;
    case DraggableElement::FullBox:
        TranslateUsingHandleMovement(m_lastDragPoint, pt);
        break;
    default:
        break;
    }

    m_lastDragPoint = pt;
}

void SelectionBox::FinishDragging()
{
    m_draggableElement = {};
}

void SelectionBox::PredefinedRotate(double angle)
{
    m_object.get().UpdateRotationAngle(angle);
}

wxPoint2DDouble SelectionBox::GetRotationHandleStart() const
{
    const auto box = m_object.get().GetBoundingBox();
    return ObjectSpace::ToScreenCoordinates(m_object.get(), box.GetLeftBottom() + wxPoint2DDouble{box.m_width / 2.0, 0.0});
}

wxPoint2DDouble SelectionBox::GetRotationHandleCenter() const
{
    const auto box = m_object.get().GetBoundingBox();
    const auto handleDistanceY = m_handleWidth * 2.0 / std::fabs(m_object.get().GetTransformation().scaleY);
    const auto boxBottomCenter = box.GetLeftBottom() + wxPoint2DDouble{box.m_width / 2.0, 0.0};

    return ObjectSpace::ToScreenCoordinates(m_object.get(), {boxBottomCenter.m_x, boxBottomCenter.m_y + handleDistanceY});
}

wxPoint2DDouble SelectionBox::GetTopLeftHandleCenter() const
{
    return ObjectSpace::ToScreenCoordinates(m_object.get(), m_object.get().GetBoundingBox().GetLeftTop());
}

wxPoint2DDouble SelectionBox::GetTopRightHandleCenter() const
{
    return ObjectSpace::ToScreenCoordinates(m_object.get(), m_object.get().GetBoundingBox().GetRightTop());
}

wxPoint2DDouble SelectionBox::GetBottomLeftHandleCenter() const
{
    return ObjectSpace::ToScreenCoordinates(m_object.get(), m_object.get().GetBoundingBox().GetLeftBottom());
}

wxPoint2DDouble SelectionBox::GetBottomRightHandleCenter() const
{
    return ObjectSpace::ToScreenCoordinates(m_object.get(), m_object.get().GetBoundingBox().GetRightBottom());
}

void SelectionBox::DrawHandle(wxGraphicsContext &gc, wxPoint2DDouble center) const
{
    gc.PushState();

    gc.Translate(center.m_x, center.m_y);
    gc.Rotate(m_object.get().GetTransformation().rotationAngle);

    gc.SetPen(*wxBLACK_PEN);
    gc.SetBrush(*wxWHITE_BRUSH);
    gc.DrawRectangle(-m_handleWidth / 2, -m_handleWidth / 2, m_handleWidth, m_handleWidth);

    gc.PopState();
}

bool SelectionBox::HandleHitTest(wxPoint2DDouble point, wxPoint2DDouble handleCenter) const
{
    wxAffineMatrix2D screenToHandleMatrix;

    screenToHandleMatrix.Translate(handleCenter.m_x, handleCenter.m_y);
    screenToHandleMatrix.Rotate(m_object.get().GetTransformation().rotationAngle);
    screenToHandleMatrix.Invert();

    return wxRect2DDouble{-m_handleWidth / 2, -m_handleWidth / 2, m_handleWidth, m_handleWidth}.Contains(screenToHandleMatrix.TransformPoint(point));
}

bool SelectionBox::FullBoxHitTest(wxPoint2DDouble point) const
{
    return m_object.get().GetBoundingBox().Contains(ObjectSpace::ToObjectCoordinates(m_object.get(), point));
}

void SelectionBox::ScaleUsingHandleMovement(wxPoint2DDouble dragStart, wxPoint2DDouble dragEnd, wxPoint2DDouble handleCenter)
{
    const auto directionFromCenter = ObjectSpace::ToObjectCoordinates(m_object.get(), handleCenter) - m_object.get().GetBoundingBox().GetCentre();
    const auto dragInObjectSpace = ObjectSpace::ToObjectDistance(m_object.get(), dragEnd - dragStart);

    const auto [halfBoxWidth, halfBoxHeight] = m_object.get().GetBoundingBox().GetSize() / 2;
    const auto halfWidthAdjusment = directionFromCenter.m_x > 0 ? dragInObjectSpace.m_x : -dragInObjectSpace.m_x;
    const auto halfHeightAdjusment = directionFromCenter.m_y > 0 ? dragInObjectSpace.m_y : -dragInObjectSpace.m_y;

    m_object.get().UpdateScaleFactor((halfBoxWidth + halfWidthAdjusment) / halfBoxWidth, (halfBoxHeight + halfHeightAdjusment) / halfBoxHeight);
}

void SelectionBox::RotateUsingHandleMovement(wxPoint2DDouble dragStart, wxPoint2DDouble dragEnd)
{
    const auto objectCenterOnScreen = ObjectSpace::ToScreenCoordinates(m_object.get(), m_object.get().GetBoundingBox().GetCentre());

    const auto v1 = dragStart - objectCenterOnScreen;
    const auto v2 = dragEnd - objectCenterOnScreen;

    const auto dotProduct = v1.m_x * v2.m_x + v1.m_y * v2.m_y;
    const auto crossProduct = v1.m_x * v2.m_y - v1.m_y * v2.m_x;
    const auto angle = std::atan2(crossProduct, dotProduct);

    m_object.get().UpdateRotationAngle(angle);
}

void SelectionBox::TranslateUsingHandleMovement(wxPoint2DDouble dragStart, wxPoint2DDouble dragEnd)
{
    const auto dragVector = dragEnd - dragStart;
    m_object.get().UpdateTranslation(dragVector.m_x, dragVector.m_y);
}
