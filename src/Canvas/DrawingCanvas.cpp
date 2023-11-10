#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "DrawingCanvas.h"
#include <iostream>

DrawingCanvas::DrawingCanvas(wxWindow *parent, DrawingView *view, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size), view(view)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);
}

void DrawingCanvas::BuildContextMenu()
{
    auto save = contextMenu->Append(wxID_ANY, "&Export...");

    this->Bind(
        wxEVT_MENU,
        [&](wxCommandEvent &)
        {
            this->ShowExportDialog();
        },
        save->GetId());
}

void DrawingCanvas::ShowExportDialog()
{
    if (view)
    {
        wxFileDialog exportFileDialog(this, _("Export drawing"), "", "",
                                      "Bitmap Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png|JPEG Files (*.jpg)|*.jpg|All Files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (exportFileDialog.ShowModal() == wxID_CANCEL)
            return;

        wxBitmap bitmap(this->GetSize() * this->GetContentScaleFactor());

        wxMemoryDC memDC;

        memDC.SetUserScale(this->GetContentScaleFactor(), this->GetContentScaleFactor());
        memDC.SelectObject(bitmap);

        view->OnDraw(&memDC);

        bitmap.SaveFile(exportFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
        bitmap.SaveFile(exportFileDialog.GetPath(), wxBITMAP_TYPE_JPEG);
        bitmap.SaveFile(exportFileDialog.GetPath(), wxBITMAP_TYPE_BMP);
    }
}

void DrawingCanvas::OnMouseDown(wxMouseEvent &event)
{
    view->OnMouseDown(event.GetPosition());
    isDragging = true;
    Refresh();
}

void DrawingCanvas::OnMouseMove(wxMouseEvent &event)
{
    if (isDragging)
    {
        view->OnMouseDrag(event.GetPosition());
        Refresh();
    }
}

void DrawingCanvas::OnMouseUp(wxMouseEvent &event)
{
    if (isDragging)
    {
        isDragging = false;
        view->OnMouseDragEnd();
    }
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent &event)
{
    if (isDragging)
    {
        isDragging = false;
        view->OnMouseDragEnd();
    }
}

void DrawingCanvas::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);

    if (view)
    {
        view->OnDraw(&dc);
    }
}

void DrawingCanvas::SetView(DrawingView *view)
{
    this->view = view;
    Refresh();
}

void DrawingCanvas::SetMenu(wxMenu *menu)
{
    this->contextMenu = menu;
}
