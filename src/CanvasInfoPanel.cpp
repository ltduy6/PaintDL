#include "CanvasInfoPanel.h"

void CanvasInfoPanel::Setup(wxPanel *panel)
{
    m_panel = panel;
}

void CanvasInfoPanel::SetUpSlider(std::function<void(int)> callback)
{
    m_slider->Bind(wxEVT_SCROLL_THUMBRELEASE, [callback, this](wxScrollEvent &event)
                   { callback(event.GetPosition()); });
}

void CanvasInfoPanel::SetUpChoice(std::function<void(double)> callback)
{
}
