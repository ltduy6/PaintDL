#include "ShapeCommand.h"

ShapeCommand::ShapeCommand(DrawingCanvas *canvas, wxString name) : wxCommand(true, name), m_canvas(canvas)
{
    m_object = new CanvasObject(m_canvas->GetView()->GetCanvasObject());
}

ShapeCommand::~ShapeCommand()
{
    if (m_object)
    {
        delete m_object;
    }
}

bool ShapeCommand::Do()
{
    m_canvas->GetView()->GetDocument()->objects.push_back(*m_object);
    m_canvas->GetView()->GetDocument()->Modify(true);
    m_canvas->Refresh();
    return true;
}

bool ShapeCommand::Undo()
{
    m_canvas->GetView()->GetDocument()->objects.pop_back();
    m_canvas->ReFreshCanvas();
    return true;
}
