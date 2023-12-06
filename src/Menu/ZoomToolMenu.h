#pragma once

#include "ToolMenu.h"
#include "MenuTemplate.h"
#include "ZoomMenu.h"
#include <wx/combobox.h>
#include <wx/wrapsizer.h>

class ZoomToolMenu : public ToolMenu
{
public:
    ZoomToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    void CallZoom(DrawingCanvas *canvas);
    void CallUpdateZoomComboBox(double zoomFactor);
    ~ZoomToolMenu() = default;

private:
    ZoomMenu zoomMenu;
};