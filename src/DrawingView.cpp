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
    dc->SetBackground(*wxWHITE_BRUSH);
    dc->Clear();

    std::unique_ptr<wxGraphicsContext> gc{wxGraphicsContext::CreateFromUnknownDC(*dc)};

    if (gc)
    {
        for (const auto &obj : GetDocument()->objects)
        {
            obj.get().Draw(*gc);
        }

        if (selectionBox)
        {
            selectionBox->Draw(*gc);
        }

        shapeCreator.Draw(*gc);
    }
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
                std::cout << "Yes" << std::endl;
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
        }
        else
        {
            selectionBox = {};
            shapeCreator.Start(MyApp::GetStrokeSettings(), pt);
        }
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
        if (!GetIsModified())
        {
            auto iterator = GetDocument()->objects.back();
            selectionBox = std::make_optional(SelectionBox{iterator, MyApp::GetStrokeSettings().selectionHandleWidth});
        }
        break;
    }
    }
}

void DrawingView::OnKeyDown(wxKeyEvent &event)
{
    if (selectionBox.has_value())
    {
        if (event.GetKeyCode() != WXK_BACK)
        {
            selectionBox->UpdateKey(event.GetUnicodeKey());
        }
        else
        {
            selectionBox->UpdateKey(event.GetUnicodeKey(), true);
        }
    }
}

void DrawingView::OnClear()
{
    GetDocument()->shapes.clear();
    GetDocument()->Modify(true);
}

void DrawingView::AddPointToCurrentLine(wxPoint pt)
{
    auto &currentSquiggle = GetDocument()->lines.back();

    currentSquiggle.points.push_back(pt);
    GetDocument()->Modify(true);
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
    CanvasObject::globalScaleFactor = scaleFactor;
    for (auto &obj : GetDocument()->objects)
    {
        obj.get().SetScaleMatrix(scaleFactor, center);
    }
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
