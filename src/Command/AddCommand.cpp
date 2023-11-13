#include "AddCommand.h"
#include "../MyApp.h"

AddCommand::AddCommand(DrawingCanvas *canvas) : wxCommand(true, "Add"), m_canvas(canvas)
{
    m_object = new CanvasObject(m_canvas->GetView()->GetCanvasObject());
}

AddCommand::~AddCommand()
{
    if (m_object)
    {
        delete m_object;
    }
}

bool AddCommand::Do()
{
    m_canvas->GetView()->GetDocument()->objects.push_back(*m_object);
    m_canvas->GetView()->GetDocument()->Modify(true);
    m_canvas->Refresh();
    return true;
}

bool AddCommand::Undo()
{
    m_canvas->GetView()->GetDocument()->objects.pop_back();
    m_canvas->ReFreshCanvas();
    return true;
}
