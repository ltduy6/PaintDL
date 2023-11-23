#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "DrawingCanvas.h"
#include "../Command/AddCommand.h"
#include "../Command/SelectionCommand.h"
#include "../Command/ShapeCommand.h"
#include "../MyApp.h"
#include <iostream>

DrawingCanvas::DrawingCanvas(wxWindow *parent, DrawingView *view, HistoryPanel &historyPanel, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size), view(view), m_historyPanel(historyPanel)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);
    view->Bind(wxEVT_CHAR_HOOK, &DrawingCanvas::OnKeyDown, this);
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

void DrawingCanvas::RotateCommand()
{
    if (view->GetIsSelected() && MyApp::GetStrokeSettings().currentTool == ToolType::Transform)
    {
        view->PredefinedRotate(M_PI / 2);
        Refresh();
        HistoryPane *historyPane = m_historyPanel.get().createHistoryPane("Transform");
        auto command = new SelectionCommand(this, historyPane);
        view->GetDocument()->GetCommandProcessor()->Submit(command);
        m_historyPanel.get().AddHistoryItem(view->GetDocument()->GetCommandProcessor(), historyPane);
    }
}

void DrawingCanvas::CallScale(double scaleFactor)
{
    if (view)
    {
        view->SetScaleObjects(scaleFactor, wxPoint2DDouble(this->GetParent()->GetClientSize().x / 2, this->GetParent()->GetClientSize().y / 2));
        Refresh();
    }
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
    if (isDragging && MyApp::GetStrokeSettings().currentTool != ToolType::Text)
    {
        view->OnMouseDragEnd();
        isDragging = false;
        if (MyApp::GetStrokeSettings().currentTool != ToolType::Transform)
        {
            HistoryPane *historyPane = m_historyPanel.get().createHistoryPane(getShapeCommandName());
            auto command = new AddCommand(this, getShapeCommandName(), historyPane);
            view->GetDocument()->GetCommandProcessor()->Submit(command);
            m_historyPanel.get().AddHistoryItem(view->GetDocument()->GetCommandProcessor(), historyPane);
        }
        else if (view->GetIsModified())
        {
            HistoryPane *historyPane = m_historyPanel.get().createHistoryPane("Transform");
            auto command = new SelectionCommand(this, historyPane);
            view->GetDocument()->GetCommandProcessor()->Submit(command);
            m_historyPanel.get().AddHistoryItem(view->GetDocument()->GetCommandProcessor(), historyPane);
            view->ResetModified();
        }
    }
    else if (MyApp::GetStrokeSettings().currentTool == ToolType::Text)
    {
        isDragging = false;
        if (!view->GetIsModified())
        {
            HistoryPane *historyPane = m_historyPanel.get().createHistoryPane("Text");
            auto command = new AddCommand(this, "Text", historyPane, false);
            view->GetDocument()->GetCommandProcessor()->Submit(command);
            m_historyPanel.get().AddHistoryItem(view->GetDocument()->GetCommandProcessor(), historyPane);
        }
        view->OnMouseDragEnd();
    }
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent &event)
{
    if (MyApp::GetStrokeSettings().currentTool != ToolType::Text)
    {
        OnMouseUp(event);
    }
}

void DrawingCanvas::OnScroll(wxScrollEvent &event)
{
    std::cout << "Yes\n";
    Refresh();
}

void DrawingCanvas::OnKeyDown(wxKeyEvent &event)
{
    view->OnKeyDown(event);
    Refresh();
    event.Skip();
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
    case ShapeType::Text:
        return "Text";
    default:
        return "Shape";
    }
}

void DrawingCanvas::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);

    if (view)
    {
        wxDouble x = GetClientSize().x / 2;
        wxDouble y = GetClientSize().y / 2;
        view->SetCenter(wxPoint(x, y));
        view->OnDraw(&dc);
    }
}

void DrawingCanvas::SetView(DrawingView *view)
{
    this->view = view;
    Refresh();
}
