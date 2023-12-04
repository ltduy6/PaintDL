#pragma once

#include <wx/wx.h>
#include <vector>
#include <memory>
#include <wx/scrolwin.h>

#include "../DrawingView.h"
#include "../Menu/HistoryPane.h"
#include "../Menu/HistoryPanel.h"

class DrawingCanvas : public wxWindow
{
public:
    typedef std::unique_ptr<DrawingCanvas> Ptr;

public:
    DrawingCanvas(wxWindow *parent, DrawingView *view, HistoryPanel &historyPanel, wxWindowID id, const wxPoint &pos, const wxSize &size);
    virtual ~DrawingCanvas() noexcept {}

    void SetView(DrawingView *view);
    void ShowExportDialog();
    void ReFreshCanvas();
    void RotateCommand();
    void Zoom(double zoomFactor);
    DrawingView *GetView() const;

private:
    void OnPaint(wxPaintEvent &event);
    void DrawOnContext(wxGraphicsContext *gc);

    void OnMouseDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnMouseUp(wxMouseEvent &event);
    void OnMouseLeave(wxMouseEvent &event);
    void OnScroll(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent &event);
    void HandleEvent(wxMouseEvent &event);
    void UpdateHistoryPanel();

    void CenterAfterZoom(wxPoint previousCenter, wxPoint currentCenter);
    void SetUpVirtualSize();

    wxString getShapeCommandName();
    wxRect getCanvasBound() const;

private:
    DrawingView *view;
    std::reference_wrapper<HistoryPanel> m_historyPanel;
    wxPoint2DDouble m_lastZoomCenter{};
    double m_zoomFactor{1};
    int m_zoomLevel{0};
    bool isDragging{false};
    bool isFirstScroll{true};
};