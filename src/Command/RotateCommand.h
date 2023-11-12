#pragma once

#include <wx/cmdproc.h>
#include "../Canvas/DrawingCanvas.h"
#include "../DrawingDocument.h"

class RotateCommand : public wxCommand
{
public:
    RotateCommand(const wxString &name, int cmd, DrawingDocument *doc, DrawingCanvas *canvas, double angle);
    ~RotateCommand();

    virtual bool Do();
    virtual bool Undo();

    bool DoOrUndo(int cmd);

protected:
    DrawingDocument *m_doc{};
    DrawingCanvas *m_canvas{};
    double m_angle{};
    bool m_cmd{};
};