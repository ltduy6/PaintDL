#pragma once

#include <wx/cmdproc.h>
#include "../Canvas/ShapeCreator.h"
#include "../Canvas/DrawingCanvas.h"

class AddCommand : public wxCommand
{
public:
    AddCommand(DrawingCanvas *canvas);
    ~AddCommand();

    virtual bool Do() override;
    virtual bool Undo() override;

private:
    DrawingCanvas *m_canvas{};
    CanvasObject *m_object{};
};
