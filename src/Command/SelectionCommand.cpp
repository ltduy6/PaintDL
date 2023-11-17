#include "SelectionCommand.h"

SelectionCommand::SelectionCommand(DrawingCanvas *canvas, HistoryPane *historyPane)
    : m_canvas(canvas), m_historyPane(historyPane), wxCommand(true, "Selection Tool"), m_object(canvas->GetView()->GetSelectionBox().GetObject())
{
}

SelectionCommand::~SelectionCommand()
{
    if (m_historyPane)
    {
        m_historyPane->Hide();
    }
}

bool SelectionCommand::Do()
{
    m_historyPane->SetActive(true);
    m_historyPane->Refresh();
    if (firstDo)
    {
        m_oldTransform = m_canvas->GetView()->GetSelectionBox().GetTransformation();
        m_newTransform = m_canvas->GetView()->GetSelectionBox().GetObject().GetTransformation();
        firstDo = false;
    }
    else
    {
        m_object.get().SetRotationAngle(m_newTransform.rotationAngle);
        m_object.get().SetScaleFactor(m_newTransform.scaleX, m_newTransform.scaleY);
        m_object.get().SetTranslation(m_newTransform.translationX, m_newTransform.translationY);
        m_canvas->Refresh();
    }
    return true;
}

bool SelectionCommand::Undo()
{
    m_historyPane->SetActive(false);
    m_historyPane->Refresh();
    m_object.get().SetRotationAngle(m_oldTransform.rotationAngle);
    m_object.get().SetScaleFactor(m_oldTransform.scaleX, m_oldTransform.scaleY);
    m_object.get().SetTranslation(m_oldTransform.translationX, m_oldTransform.translationY);
    m_canvas->Refresh();
    return true;
}
