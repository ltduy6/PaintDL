#pragma once

#include "../MyApp.h"
#include "ToolsPane.h"
#include "RoundedButton.h"
#include "../Canvas/DrawingCanvas.h"
#include "MenuTemplate.h"

class ImageMenu : public MenuTemplate
{
public:
    void SetUpImageMenu(wxWindow *parent, wxSizer *sizer, wxStaticText *text);
    void CallRotate(DrawingCanvas *canvas);
    ToolsPane *GetRotatePane() const;

private:
    ToolsPane *rotatePane{};
    wxMenu *rotateMenu;
    const std::vector<ToolType> imageTypes = {ToolType::Rotate};
};
