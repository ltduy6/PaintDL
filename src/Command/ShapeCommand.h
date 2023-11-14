#pragma once

#include <wx/cmdproc.h>
#include "../Canvas/ShapeCreator.h"
#include "../Canvas/DrawingCanvas.h"

class ShapeCommand : public wxCommand
{
public:
    ShapeCommand(DrawingCanvas *canvas, wxString name);
    ~ShapeCommand();

    virtual bool Do() override;
    virtual bool Undo() override;

private:
    DrawingCanvas *m_canvas{};
    CanvasObject *m_object{};
};
