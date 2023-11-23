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
    if (m_choice != nullptr)
    {
        m_choice->Destroy();
    }
    wxArrayString choices;
    choices.Add("50%");
    choices.Add("100%");
    choices.Add("150%");
    choices.Add("200%");

    m_choice = new wxChoice(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
    m_choice->SetSelection(1);
    m_choice->Bind(wxEVT_CHOICE, [callback, this](wxCommandEvent &event)
                   {
                       switch (event.GetSelection())
                       {
                       case 0:
                           callback(0.5);
                           break;
                       case 1:
                           callback(1);
                           break;
                       case 2:
                           callback(1.5);
                           break;
                       case 3:
                           callback(2);
                           break;
                       } });
}
