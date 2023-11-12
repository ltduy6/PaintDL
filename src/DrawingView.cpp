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
        std::cout << "Object\n";
        for (const auto &obj : GetDocument()->objects)
        {
            obj.Draw(*gc);
        }
        std::cout << "SelectionBox\n";

        if (selectionBox)
        {
            selectionBox->Draw(*gc);
        }

        std::cout << "ShapeCreator\n";

        shapeCreator.Draw(*gc);
    }
}

void DrawingView::OnMouseDown(wxPoint pt)
{
    if (MyApp::GetStrokeSettings().currentTool == ToolType::Transform)
    {
        if (selectionBox.has_value())
        {
            selectionBox->StartDragging(pt);
        }

        bool clickedOnCurrentSelection = selectionBox.has_value() && selectionBox->isDragging();

        if (!clickedOnCurrentSelection)
        {
            std::cout << GetDocument()->objects.size() << std::endl;
            auto iterator = std::find_if(GetDocument()->objects.rbegin(), GetDocument()->objects.rend(), [&](auto &obj)
                                         { return obj.GetBoundingBox().Contains(ObjectSpace::ToObjectCoordinates(obj, pt)); });
            std::cout << GetDocument()->objects.size() + 1 << std::endl;
            selectionBox = (iterator != GetDocument()->objects.rend()) ? std::make_optional(SelectionBox{*iterator, MyApp::GetStrokeSettings().selectionHandleWidth}) : std::nullopt;

            if (selectionBox.has_value())
            {
                std::cout << GetDocument()->objects.size() << std::endl;
                selectionBox->StartDragging(pt);
            }
        }
    }
    else
    {
        selectionBox = {};
        shapeCreator.Start(MyApp::GetStrokeSettings(), pt);
    }
}

void DrawingView::OnMouseDrag(wxPoint pt)
{
    if (MyApp::GetStrokeSettings().currentTool == ToolType::Transform)
    {
        if (selectionBox.has_value() && selectionBox->isDragging())
        {
            selectionBox->Drag(pt);
            GetDocument()->Modify(true);
        }
    }
    else
    {
        shapeCreator.Update(pt);
    }
}

void DrawingView::OnMouseDragEnd()
{
    // Nothing to do here
    if (MyApp::GetStrokeSettings().currentTool == ToolType::Transform)
    {
        if (selectionBox.has_value())
        {
            selectionBox->FinishDragging();
        }
    }
    else
    {
        selectionBox = {};
        // GetDocument()->objects.push_back(shapeCreator.FinishAndGenerateObject());
        // GetDocument()->Modify(true);
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
