#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "DrawingCanvas.h"
#include "../Command/AddCommand.h"
#include "../Command/SelectionCommand.h"
#include "../Command/ShapeCommand.h"
#include "../MyApp.h"
#include <iostream>

DrawingCanvas::DrawingCanvas(wxWindow *parent, DrawingView *view, wxWindowID id, HistoryPanel &historyPanel, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size), view(view), m_historyPanel(historyPanel)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);
}

void DrawingCanvas::ShowExportDialog()
{
    std::cout << "ViewSHowExportDialog\n";
    if (view)
    {
        std::cout << "ShowExportDialog\n";
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

void DrawingCanvas::ReFreshCanvas()
{
    view->Refresh();
    Refresh();
}

DrawingView *DrawingCanvas::GetView() const
{
    return view;
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
        if (MyApp::GetStrokeSettings().currentTool != ToolType::Transform)
        {
            auto command = new AddCommand(this, getShapeCommandName());
            view->GetDocument()->GetCommandProcessor()->Submit(command);
            UpdateHistoryPanel();
        }
        else if (view->GetIsModified())
        {
            auto command = new SelectionCommand(this);
            view->GetDocument()->GetCommandProcessor()->Submit(command);
            UpdateHistoryPanel();
        }
    }
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent &event)
{
    OnMouseUp(event);
}

void DrawingCanvas::OnScroll(wxScrollEvent &event)
{
    std::cout << "Yes\n";
    Refresh();
}

void DrawingCanvas::HandleEvent(wxMouseEvent &event)
{
    std::cout << "Yes\n";
    if (event.GetEventType() == wxEVT_LEFT_DOWN)
    {
        std::cout << "Mouse Down\n";
        OnMouseDown(event);
    }
    else if (event.GetEventType() == wxEVT_MOTION)
    {
        OnMouseMove(event);
    }
    else if (event.GetEventType() == wxEVT_LEFT_UP)
    {
        OnMouseUp(event);
    }
    else if (event.GetEventType() == wxEVT_LEAVE_WINDOW)
    {
        OnMouseLeave(event);
    }
}
void DrawingCanvas::UpdateHistoryPanel()
{
    wxString name = view->GetDocument()->GetCommandProcessor()->GetCurrentCommand()->GetName();
    m_historyPanel.get().AddHistoryItem(name, []() {});
}

wxString DrawingCanvas::getShapeCommandName()
{
    if (MyApp::GetStrokeSettings().currentTool == ToolType::Brush)
        return "Brush Tool";
    switch (MyApp::GetStrokeSettings().currentShape)
    {
    case ShapeType::Rect:
        return "Rectangle";
    case ShapeType::Circle:
        return "Circle";
    case ShapeType::Diamond:
        return "Diamond";
    case ShapeType::ITriangle:
        return "ITriangle";
    case ShapeType::RTriangle:
        return "RTriangle";
    default:
        return "Shape";
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
