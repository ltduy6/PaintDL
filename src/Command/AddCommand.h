#pragma once

#include <wx/cmdproc.h>
#include "../Canvas/ShapeCreator.h"
#include "../Canvas/DrawingCanvas.h"
#include "../Menu/HistoryPane.h"

class AddCommand : public wxCommand
{
public:
    AddCommand(DrawingCanvas *canvas, wxString name, HistoryPane *historyPane, bool canRotate = true);
    ~AddCommand();

    virtual bool Do() override;
    virtual bool Undo() override;

private:
    DrawingCanvas *m_canvas{};
    CanvasObject *m_object{};
    HistoryPane *m_historyPane{};
};
