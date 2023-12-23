#pragma once

#include <wx/cmdproc.h>
#include "../Canvas/ShapeCreator.h"
#include "../Canvas/DrawingCanvas.h"
#include "../Menu/HistoryPane.h"

class DeleteCommand : public wxCommand
{
public:
    DeleteCommand(DrawingCanvas *canvas, HistoryPane *historyPane);
    ~DeleteCommand();

    virtual bool Do() override;
    virtual bool Undo() override;

private:
    DrawingCanvas *m_canvas{};
    std::reference_wrapper<CanvasObject> m_object;
    HistoryPane *m_historyPane{};
};