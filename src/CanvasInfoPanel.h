#pragma once

#include <wx/wx.h>

class CanvasInfoPanel
{
public:
    void Setup(wxPanel *panel);
    void SetUpSlider(std::function<void(int)> callback);
    void SetUpChoice(std::function<void(double)> callback);
private:
    wxPanel *m_panel;
    wxSlider *m_slider;
    wxChoice *m_choice;
};