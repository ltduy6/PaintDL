#include <wx/graphics.h>

#include "DrawingView.h"
#include "MyApp.h"
#include "Canvas/DrawingCanvas.h"
#include "Canvas/DrawingVisistor.h"
#include "Helper/Visistor.h"
#include "Shape/ShapeFactory.h"

#include <memory>

wxIMPLEMENT_DYNAMIC_CLASS(DrawingView, wxView);

bool DrawingView::OnCreate(wxDocument *doc, long flags)
{
    if (!wxView::OnCreate(doc, flags))
    {
        return false;
    }

    MyApp::SetupCanvasForView(this);

    return true;
}

bool DrawingView::OnClose(bool deleteWindow)
{
    if (deleteWindow)
    {
        MyApp::SetupCanvasForView(nullptr);
    }
    return wxView::OnClose(deleteWindow);
}

void DrawingView::OnChangeFilename()
{
    wxString appName = wxTheApp->GetAppDisplayName();
    wxString title;

    wxString docName = GetDocument()->GetUserReadableName();
    title = docName + (GetDocument()->IsModified() ? " - Edited" : "") + wxString(_(" - ")) + appName;

    GetFrame()->SetLabel(title);
}

void DrawingView::OnDraw(wxDC *dc)
{
    dc->SetBackground(*wxTRANSPARENT_BRUSH);
    dc->Clear();

    std::unique_ptr<wxGraphicsContext> gc{wxGraphicsContext::CreateFromUnknownDC(*dc)};

    if (gc)
    {
        gc->SetBrush(wxColour(40, 40, 40));
        gc->DrawRectangle(0, 0, this->m_virtualSize.GetWidth(), this->m_virtualSize.GetHeight());
        gc->SetBrush(*wxWHITE_BRUSH);

        if (!isExporting)
            gc->SetTransform(gc->CreateMatrix(m_zoomMatrix));

        gc->DrawRectangle(this->m_canvasBound.GetLeft(), this->m_canvasBound.GetTop(), this->m_canvasBound.GetWidth(), this->m_canvasBound.GetHeight());

        for (const auto &obj : GetDocument()->objects)
        {
            obj.get().Draw(*gc, isExporting);
        }

        if (selectionBox)
        {
            selectionBox->Draw(*gc, isExporting);
        }

        shapeCreator.Draw(*gc);
    }
}

void DrawingView::SetExporting(bool isExporting)
{
    this->isExporting = isExporting;
}

void DrawingView::OnMouseDown(wxPoint pt)
{
    switch (MyApp::GetStrokeSettings().currentTool)
    {
    case ToolType::Brush:
    {
        selectionBox = {};
        shapeCreator.Start(MyApp::GetStrokeSettings(), pt);
        break;
    }
    case ToolType::Shape:
    {
        selectionBox = {};
        shapeCreator.Start(MyApp::GetStrokeSettings(), pt);
        break;
    }
    case ToolType::Transform:
    {
        if (selectionBox.has_value())
        {
            selectionBox->StartDragging(pt);
        }

        bool clickedOnCurrentSelection = selectionBox.has_value() && selectionBox->isDragging();

        if (!clickedOnCurrentSelection)
        {
            auto iterator = std::find_if(GetDocument()->objects.rbegin(), GetDocument()->objects.rend(), [&](auto &obj)
                                         { return obj.get().GetBoundingBox().Contains(ObjectSpace::ToObjectCoordinates(obj, pt)); });

            selectionBox = (iterator != GetDocument()->objects.rend()) ? std::make_optional(SelectionBox{*iterator, MyApp::GetStrokeSettings().selectionHandleWidth}) : std::nullopt;

            if (selectionBox.has_value())
            {
                selectionBox->StartDragging(pt);
            }
        }
        break;
    }
    case ToolType::Text:
    {
        if (selectionBox.has_value())
        {
            selectionBox->StartDragging(pt);
            if (selectionBox->isDragging())
                isModified = true;
        }
        if (selectionBox.has_value() && !selectionBox->isDragging() || !selectionBox.has_value())
        {
            selectionBox = {};
            shapeCreator.Start(MyApp::GetStrokeSettings(), pt);
        }
        break;
    }
    case ToolType::Move:
    {
        lastDragStart = pt;
        isMoving = true;
        break;
    }
    default:
    {
        break;
    }
    }
}

void DrawingView::OnMouseDrag(wxPoint pt)
{
    switch (MyApp::GetStrokeSettings().currentTool)
    {
    case ToolType::Brush:
    {
        shapeCreator.Update(pt);
        break;
    }
    case ToolType::Shape:
    {
        shapeCreator.Update(pt);
        break;
    }
    case ToolType::Transform:
    {
        if (selectionBox.has_value() && selectionBox->isDragging())
        {
            isModified = true;
            selectionBox->Drag(pt);
            GetDocument()->Modify(true);
        }
        break;
    }
    case ToolType::Text:
    {
        if (selectionBox.has_value() && selectionBox->isDragging())
        {
            isModified = true;
            selectionBox->Drag(pt);
            GetDocument()->Modify(true);
        }
        break;
    }
    case ToolType::Move:
    {
        if (isMoving)
        {
            auto translateX = pt.x - lastDragStart.x;
            auto translateY = pt.y - lastDragStart.y;

            SetTransLateFactor(translateX, translateY);

            lastDragStart = pt;
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

void DrawingView::OnMouseDragEnd()
{
    // Nothing to do here
    switch (MyApp::GetStrokeSettings().currentTool)
    {
    case ToolType::Transform:
    {
        if (selectionBox.has_value())
        {
            selectionBox->FinishDragging();
        }
        break;
    }
    case ToolType::Brush:
    {
        selectionBox = {};
        break;
    }
    case ToolType::Shape:
    {
        selectionBox = {};
        break;
    }
    case ToolType::Text:
    {
        if (selectionBox.has_value() && !selectionBox->isDragging())
        {
            selectionBox->FinishDragging();
        }
        else
        {
            selectionBox = {};
        }
        if (!GetIsModified())
        {
            auto iterator = GetDocument()->objects.back();
            selectionBox = std::make_optional(SelectionBox{iterator, MyApp::GetStrokeSettings().selectionHandleWidth});
        }
        break;
    }
    case ToolType::Move:
    {
        isMoving = false;
        break;
    }
    default:
    {
        break;
    }
    }
}

void DrawingView::OnKeyDown(wxKeyEvent &event)
{
    if (selectionBox.has_value())
    {
        if (event.GetUnicodeKey() == WXK_NONE)
        {
            return;
        }
        switch (event.GetKeyCode())
        {
        case WXK_BACK:
            selectionBox->UpdateKey(event.GetUnicodeKey(), true);
            break;
        case WXK_CAPITAL:
            break;
        case WXK_TAB:
            break;
        case WXK_RETURN:
            selectionBox->UpdateKey('\n');
            break;
        default:
            selectionBox->UpdateKey(GetCharFromKeycode(event.GetUnicodeKey()));
            break;
        }
    }
}

void DrawingView::OnClear()
{
    GetDocument()->objects.clear();
    GetDocument()->Modify(true);
}

void DrawingView::UpdateZoomMatrix()
{
    for (auto &obj : GetDocument()->objects)
    {
        obj.get().UpdateZoomMatrix(m_zoomMatrix);
    }
    shapeCreator.UpdateZoomMatrix(m_zoomMatrix);
}

wxChar DrawingView::GetCharFromKeycode(int keycode)
{
    if (wxGetKeyState(WXK_SHIFT))
    {
        switch (keycode)
        {
        case '1':
            return '!';
        case '2':
            return '@';
        case '3':
            return '#';
        case '4':
            return '$';
        case '5':
            return '%';
        case '6':
            return '^';
        case '7':
            return '&';
        case '8':
            return '*';
        case '9':
            return '(';
        case '0':
            return ')';
        case '-':
            return '_';
        case '=':
            return '+';
        case '[':
            return '{';
        case ']':
            return '}';
        case '\\':
            return '|';
        case ';':
            return ':';
        case '\'':
            return '"';
        case ',':
            return '<';
        case '.':
            return '>';
        case '/':
            return '?';
        default:
            break;
        }
        if (wxGetKeyState(WXK_CAPITAL))
        {
            return keycode + 32;
        }
        else
        {
            return keycode;
        }
    }
    else
    {
        if (keycode >= 'A' && keycode <= 'Z' && !wxGetKeyState(WXK_CAPITAL))
        {
            return keycode + 32;
        }
        else
        {
            return keycode;
        }
    }
}

void DrawingView::PredefinedRotate(double angle)
{
    if (selectionBox.has_value())
    {
        selectionBox->PredefinedRotate(angle);
        GetDocument()->Modify(true);
        GetDocument()->UpdateAllViews();
    }
}

void DrawingView::Refresh()
{
    if (selectionBox.has_value())
    {
        selectionBox->FinishDragging();
        selectionBox = {};
    }
}

void DrawingView::ResetModified()
{
    isModified = false;
}

void DrawingView::SetCenter(wxPoint pt)
{
    screenCenter = pt;
}

void DrawingView::SetScaleObjects(double scaleFactor, wxPoint2DDouble center)
{
}

void DrawingView::SetVirtualSize(wxSize size)
{
    m_virtualSize = size;
}

void DrawingView::SetCanvasBound(wxRect bound)
{
    m_canvasBound = bound;
}

void DrawingView::SetZoomFactor(double zoomFactor, wxPoint2DDouble center)
{
    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Translate(center.m_x, center.m_y);
    newMatrix->Scale(zoomFactor / m_currentFactor, zoomFactor / m_currentFactor);
    newMatrix->Translate(-center.m_x, -center.m_y);
    newMatrix->Concat(m_zoomMatrix);

    m_zoomMatrix = *newMatrix;
    m_currentFactor = zoomFactor;
    delete newMatrix;

    UpdateZoomMatrix();
}

void DrawingView::SetTransLateFactor(double translateX, double translateY)
{
    m_transformation.translationX += translateX;
    m_transformation.translationY += translateY;

    wxAffineMatrix2D *newMatrix = new wxAffineMatrix2D();
    newMatrix->Translate(translateX, translateY);
    newMatrix->Concat(m_zoomMatrix);
    m_zoomMatrix = *newMatrix;

    delete newMatrix;

    UpdateZoomMatrix();
}

bool DrawingView::GetIsModified() const
{
    return isModified && selectionBox.has_value();
}

bool DrawingView::GetIsSelected() const
{
    return selectionBox.has_value() && selectionBox->isCanRotate();
}

DrawingDocument *DrawingView::GetDocument() const
{
    return wxStaticCast(wxView::GetDocument(), DrawingDocument);
}

CanvasObject DrawingView::GetCanvasObject()
{
    // TODO: insert return statement here
    return shapeCreator.FinishAndGenerateObject();
}

ShapeCreator &DrawingView::GetShapeCreator()
{
    // TODO: insert return statement here
    return shapeCreator;
}

SelectionBox &DrawingView::GetSelectionBox()
{
    // TODO: insert return statement here
    return selectionBox.value();
}
