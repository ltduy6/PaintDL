#pragma once

#include <wx/wx.h>
#include <vector>
#include <memory>
#include <wx/scrolwin.h>

#include "../DrawingView.h"
#include "../Menu/HistoryPanel.h"

class DrawingCanvas : public wxWindow
{
public:
    typedef std::unique_ptr<DrawingCanvas> Ptr;

public:
    DrawingCanvas(wxWindow *parent, DrawingView *view, wxWindowID id, HistoryPanel &historyPanel, const wxPoint &pos, const wxSize &size);
    virtual ~DrawingCanvas() noexcept {}

    void SetView(DrawingView *view);
    void ShowExportDialog();
    void ReFreshCanvas();
    DrawingView *GetView() const;

private:
    void OnPaint(wxPaintEvent &event);
    void DrawOnContext(wxGraphicsContext *gc);

    void OnMouseDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnMouseUp(wxMouseEvent &event);
    void OnMouseLeave(wxMouseEvent &event);
    void OnScroll(wxScrollEvent &event);
    void HandleEvent(wxMouseEvent &event);
    void UpdateHistoryPanel();

    wxString getShapeCommandName();

private:
    DrawingView *view;
    std::reference_wrapper<HistoryPanel> m_historyPanel;
    std::vector<wxCommand *> m_commands;

    bool isDragging{false};
};