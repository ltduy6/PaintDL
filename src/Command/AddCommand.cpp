#include "AddCommand.h"
#include "../MyApp.h"

AddCommand::AddCommand(DrawingCanvas *canvas, wxString name, HistoryPane *historyPane) : wxCommand(true, name), m_canvas(canvas), m_historyPane(historyPane)
{
    m_object = new CanvasObject(m_canvas->GetView()->GetCanvasObject());
}

AddCommand::~AddCommand()
{
    if (m_object)
    {
        delete m_object;
    }
    if (m_historyPane)
    {
        m_historyPane->Hide();
    }
}

bool AddCommand::Do()
{
    m_historyPane->SetActive(true);
    m_historyPane->Refresh();
    m_canvas->GetView()->GetDocument()->objects.push_back(*m_object);
    m_canvas->GetView()->GetDocument()->Modify(true);
    m_canvas->Refresh();
    return true;
}

bool AddCommand::Undo()
{
    m_historyPane->SetActive(false);
    m_historyPane->Refresh();
    m_canvas->GetView()->GetDocument()->objects.pop_back();
    m_canvas->ReFreshCanvas();
    return true;
}
