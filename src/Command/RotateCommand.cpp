#include "RotateCommand.h"

RotateCommand::RotateCommand(const wxString &name, int cmd, DrawingDocument *doc, DrawingCanvas *canvas, double angle)
    : wxCommand(true, name), m_doc(doc), m_canvas(canvas), m_angle(angle), m_cmd(cmd)
{
}

RotateCommand::~RotateCommand()
{
    if (m_canvas)
    {
        delete m_canvas;
    }
}

bool RotateCommand::Do()
{
    return false;
}

bool RotateCommand::Undo()
{
    return false;
}

bool RotateCommand::DoOrUndo(int cmd)
{
    return false;
}
