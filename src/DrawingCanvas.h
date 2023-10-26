#pragma once
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <vector>

class DrawingCanvas : public wxWindow
{
public:
    DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
    virtual ~DrawingCanvas() noexcept {}

    void SetPenColor(const wxColour &color);
    void SetPenWidth(int width);

private:
    void OnPaint(wxPaintEvent &event);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMotion(wxMouseEvent &event);
    void OnLeave(wxMouseEvent &event);
    void OnEraseBackground(wxMouseEvent &event);
    void DrawContext(wxGraphicsContext *gc);

private:
    struct Path
    {
        wxColour color;
        int width;
        std::vector<wxPoint2DDouble> points;
    };

private:
    bool isDrawing{};
    wxColour penColor{};
    int penWidth{5};
    std::vector<Path> lines{};
};