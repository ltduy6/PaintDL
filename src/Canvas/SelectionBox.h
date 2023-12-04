#pragma once

#include <optional>
#include <wx/wx.h>

#include "CanvasObject.h"
#include "ObjectSpace.h"

class SelectionBox
{
public:
    SelectionBox(CanvasObject &object, double handleWidth);
    Transformation GetTransformation() const;
    CanvasObject &GetObject();
    void UpdateKey(wxChar key, bool isDelete = false);
    void Draw(wxGraphicsContext &gc, bool isExporting = false) const;
    void StartDragging(wxPoint2DDouble point);
    bool isDragging() const;
    bool isCanRotate() const;
    void Drag(wxPoint2DDouble pt);
    void FinishDragging();
    void PredefinedRotate(double angle);

private:
    wxPoint2DDouble GetRotationHandleStart() const;
    wxPoint2DDouble GetRotationHandleCenter() const;
    wxPoint2DDouble GetTopLeftHandleCenter() const;
    wxPoint2DDouble GetTopRightHandleCenter() const;
    wxPoint2DDouble GetBottomLeftHandleCenter() const;
    wxPoint2DDouble GetBottomRightHandleCenter() const;
    wxPoint2DDouble GetCenter() const;
    wxPoint2DDouble GetOldCenter() const;
    // wxPoint2DDouble GetMidTopHandleCenter() const;
    // wxPoint2DDouble GetMidBottomHandleCenter() const;
    // wxPoint2DDouble GetMidLeftHandleCenter() const;
    // wxPoint2DDouble GetMidRightHandleCenter() const;

    void DrawHandle(wxGraphicsContext &gc, wxPoint2DDouble center) const;

    bool HandleHitTest(wxPoint2DDouble point, wxPoint2DDouble handleCenter) const;
    bool FullBoxHitTest(wxPoint2DDouble point) const;

    void ScaleUsingHandleMovement(wxPoint2DDouble dragStart, wxPoint2DDouble dragEnd, wxPoint2DDouble handleCenter);
    void RotateUsingHandleMovement(wxPoint2DDouble dragStart, wxPoint2DDouble dragEnd);
    void TranslateUsingHandleMovement(wxPoint2DDouble dragStart, wxPoint2DDouble dragEnd);

private:
    enum class DraggableElement
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        MidTop,
        MideBottom,
        MidLeft,
        MidRight,
        Rotation,
        FullBox
    };

private:
    std::optional<DraggableElement> m_draggableElement{};
    wxPoint2DDouble m_lastDragPoint{};
    double m_handleWidth;
    double m_currentRotateAngle{0.0};
    std::reference_wrapper<CanvasObject> m_object;
    Transformation m_oldTransformation;
    wxAffineMatrix2D m_oldMatrix;
};