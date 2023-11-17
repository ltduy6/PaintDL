#pragma once

#include <wx/cmdproc.h>
#include "../Canvas/DrawingCanvas.h"
#include "../DrawingDocument.h"
#include "../Menu/HistoryPane.h"

class SelectionCommand : public wxCommand
{
public:
    SelectionCommand(DrawingCanvas *canvas, HistoryPane *historyPane);
    ~SelectionCommand();

    virtual bool Do() override;
    virtual bool Undo() override;

protected:
    DrawingCanvas *m_canvas{};
    Transformation m_oldTransform;
    Transformation m_newTransform;
    std::reference_wrapper<CanvasObject> m_object;
    HistoryPane *m_historyPane{};
    bool firstDo{true};
};