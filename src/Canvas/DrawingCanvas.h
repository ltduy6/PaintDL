#pragma once

#include <wx/wx.h>
#include <vector>
#include <memory>

#include "../DrawingView.h"

class DrawingCanvas : public wxWindow
{
public:
    typedef std::unique_ptr<DrawingCanvas> Ptr;

public:
    DrawingCanvas(wxWindow *parent, DrawingView *view, wxWindowID id, const wxPoint &pos, const wxSize &size);
    virtual ~DrawingCanvas() noexcept {}

    void SetView(DrawingView *view);
    void SetMenu(wxMenu *menu);
    void BuildContextMenu();
    void ShowExportDialog();
    DrawingView *GetView() const;

private:
    void OnPaint(wxPaintEvent &event);
    void DrawOnContext(wxGraphicsContext *gc);

    void OnMouseDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnMouseUp(wxMouseEvent &event);
    void OnMouseLeave(wxMouseEvent &event);

private:
    DrawingView *view;

    bool isDragging{false};

    wxMenu *contextMenu;
};