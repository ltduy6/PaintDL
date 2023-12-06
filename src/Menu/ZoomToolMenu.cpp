#include "ZoomToolMenu.h"

ZoomToolMenu::ZoomToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::ZoomIn)
{
    zoomMenu.SetUpZoomMenu(parent, sizer);
}

void ZoomToolMenu::ShowMenu(bool show)
{
    zoomMenu.Show(show);
}

void ZoomToolMenu::CallZoom(DrawingCanvas *canvas)
{
    zoomMenu.UpdateCanvasZoom(canvas);
}

void ZoomToolMenu::CallUpdateZoomComboBox(double zoomFactor)
{
    zoomMenu.UpdateZoomComboBox(zoomFactor);
}
