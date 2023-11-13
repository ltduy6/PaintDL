#pragma once

#include <wx/cmdproc.h>
#include "../Canvas/DrawingCanvas.h"
#include "../DrawingDocument.h"

class SelectionCommand : public wxCommand
{
public:
    SelectionCommand(DrawingCanvas *canvas);
    ~SelectionCommand();

    virtual bool Do() override;
    virtual bool Undo() override;

protected:
    DrawingCanvas *m_canvas{};
    Transformation m_oldTransform;
    Transformation m_newTransform;
    CanvasObject *m_object;
    bool firstDo{true};
};