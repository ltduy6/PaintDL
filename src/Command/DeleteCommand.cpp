#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(DrawingCanvas *canvas, HistoryPane *historyPane)
    : wxCommand(true, "Delete"), m_canvas(canvas), m_historyPane(historyPane), m_object(canvas->GetView()->GetSelectionBox().GetObject())
{
}

DeleteCommand::~DeleteCommand()
{
    if (m_historyPane)
    {
        m_historyPane->Hide();
    }
}

bool DeleteCommand::Do()
{
    auto it = std::find_if(m_canvas->GetView()->GetDocument()->objects.begin(), m_canvas->GetView()->GetDocument()->objects.end(), [&](CanvasObject &obj)
                           { return &obj == &m_object.get(); });

    if (it != m_canvas->GetView()->GetDocument()->objects.end())
    {
        m_canvas->GetView()->GetDocument()->objects.erase(it);
    }

    m_canvas->GetView()->GetDocument()->Modify(true);
    m_canvas->ReFreshCanvas();
    m_historyPane->SetActive(true);
    m_historyPane->Refresh();
    return true;
}

bool DeleteCommand::Undo()
{
    m_canvas->GetView()->GetDocument()->objects.push_back(m_object.get());
    m_canvas->ReFreshCanvas();
    m_historyPane->SetActive(false);
    m_historyPane->Refresh();
    return true;
}
