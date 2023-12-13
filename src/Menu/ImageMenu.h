#pragma once

#include "../MyApp.h"
#include "ToolsPane.h"
#include "../Canvas/DrawingCanvas.h"
#include "MenuTemplate.h"

class ImageMenu : public MenuTemplate
{
public:
    void SetUpImageMenu(wxWindow *parent, wxSizer *sizer);
    void CallRotate(DrawingCanvas *canvas);
    void PopCallback();
    ToolsPane *GetRotatePane() const;

private:
    ToolsPane *rotatePane{};
    wxMenu *rotateMenu;
    const std::vector<ToolType> imageTypes = {ToolType::Rotate};
};
