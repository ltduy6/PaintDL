#pragma once

#include "../MyApp.h"
#include "ToolsPane.h"
#include "RoundedButton.h"
#include "../Canvas/DrawingCanvas.h"

class ImageMenu
{
public:
    void SetUpImageMenu(wxWindow *parent, wxSizer *sizer);
    void CallRotate(DrawingCanvas *canvas);
    wxButton *GetRotatePane() const;

private:
    wxButton *rotatePane;
    wxMenu *rotateMenu;
    const std::vector<ToolType> imageTypes = {ToolType::Rotate};
};
