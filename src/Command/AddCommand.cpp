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
    if (MyApp::GetStrokeSettings().currentTool != ToolType::Transform)
    {
        m_canvas->GetView()->GetDocument()->objects.push_back(*m_object);
        m_canvas->Refresh();
    }
    return true;
}

bool AddCommand::Undo()
{
    m_canvas->GetView()->GetDocument()->objects.pop_back();
    m_canvas->Refresh();
    return true;
}
