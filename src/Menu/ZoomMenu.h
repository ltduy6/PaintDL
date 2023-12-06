#pragma once

#include "MenuTemplate.h"
#include "ToolsPane.h"
#include "../MyApp.h"
#include "../Canvas/DrawingCanvas.h"

#include <wx/combobox.h>

class ZoomMenu : public MenuTemplate
{
public:
    void SetUpZoomMenu(wxWindow *parent, wxSizer *sizer);
    void UpdateCanvasZoom(DrawingCanvas *drawingCanvas);
    void UpdateZoomComboBox(double zoomFactor);

private:
    wxComboBox *zoomComboBox;
};