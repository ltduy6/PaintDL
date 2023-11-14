#include "SelectionCommand.h"

SelectionCommand::SelectionCommand(DrawingCanvas *canvas) : m_canvas(canvas), m_object(nullptr), wxCommand(true, "Selection Tool")
{
}

SelectionCommand::~SelectionCommand()
{
}

bool SelectionCommand::Do()
{
    if (firstDo)
    {
        m_oldTransform = m_canvas->GetView()->GetSelectionBox().GetTransformation();
        m_newTransform = m_canvas->GetView()->GetSelectionBox().GetObject().GetTransformation();
        m_object = &m_canvas->GetView()->GetSelectionBox().GetObject();
        firstDo = false;
    }
    else
    {
        m_object->SetRotationAngle(m_newTransform.rotationAngle);
        m_object->SetScaleFactor(m_newTransform.scaleX, m_newTransform.scaleY);
        m_object->SetTranslation(m_newTransform.translationX, m_newTransform.translationY);
        m_canvas->Refresh();
    }
    return true;
}

bool SelectionCommand::Undo()
{
    m_object->SetRotationAngle(m_oldTransform.rotationAngle);
    m_object->SetScaleFactor(m_oldTransform.scaleX, m_oldTransform.scaleY);
    m_object->SetTranslation(m_oldTransform.translationX, m_oldTransform.translationY);
    m_canvas->Refresh();
    return true;
}
