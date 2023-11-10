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
        DrawingVisitor visistor{*gc};

        for (const auto &shape : GetDocument()->shapes)
        {
            std::visit(visistor, shape);
        }
    }
}

void DrawingView::OnMouseDown(wxPoint pt)
{
    lastDragStart = pt;
    GetDocument()->shapes.push_back(ShapeFactory::CreateShape(MyApp::GetStrokeSettings(), pt));
    GetDocument()->Modify(true);
}

void DrawingView::OnMouseDrag(wxPoint pt)
{
    auto &currentShape = GetDocument()->shapes.back();

    std::visit(Visitor{[&](Path &path)
                       {
                           path.points.push_back(pt);
                       },
                       [&](Rect &rect)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           rect.rect.SetLeft(left);
                           rect.rect.SetRight(right);
                           rect.rect.SetTop(top);
                           rect.rect.SetBottom(bottom);
                       },
                       [&](Circle &circle)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           circle.rect.SetLeft(left);
                           circle.rect.SetRight(right);
                           circle.rect.SetTop(top);
                           circle.rect.SetBottom(bottom);
                       },
                       [&](ITriangle &triangle)
                       {
                           triangle.drag = pt;
                       },
                       [&](RTriangle &triangle)
                       {
                           triangle.drag = pt;
                       },
                       [&](Diamond &diamond)
                       {
                           auto left = std::min(lastDragStart.x, pt.x);
                           auto right = std::max(lastDragStart.x, pt.x);
                           auto top = std::min(lastDragStart.y, pt.y);
                           auto bottom = std::max(lastDragStart.y, pt.y);

                           diamond.rect.SetLeft(left);
                           diamond.rect.SetRight(right);
                           diamond.rect.SetTop(top);
                           diamond.rect.SetBottom(bottom);
                       }},
               currentShape);
}

void DrawingView::OnMouseDragEnd()
{
    // Nothing to do here
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

DrawingDocument *DrawingView::GetDocument() const
{
    return wxStaticCast(wxView::GetDocument(), DrawingDocument);
}