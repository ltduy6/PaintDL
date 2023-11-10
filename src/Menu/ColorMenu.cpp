#include "ColorMenu.h"

void ColorMenu::SetUpColorMenu(wxWindow *parent, wxSizer *sizer, wxFrame *frame)
{
    wxSize size;
    for (const auto &color : niceColors)
    {
        auto colorPane = new ColorPane(parent, wxID_ANY, wxColour(color));
        colorPane->Bind(wxEVT_LEFT_DOWN, [this, colorPane](wxMouseEvent &event)
                        { SelectColorPane(colorPane); });
        colorPanes.push_back(colorPane);
        sizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, frame->FromDIP(5));

        size = colorPane->GetBestSize();
    }
    auto customColor = new RoundedButton(parent, wxID_ANY, "color-wheel.png", size);
    customColor->Bind(wxEVT_LEFT_DOWN, [this, frame](wxMouseEvent &event)
                      { SelectCustomColor(frame); });
    sizer->Add(customColor, 0, wxRIGHT | wxBOTTOM, frame->FromDIP(5));

    SelectColorPane(colorPanes[0]);
}

void ColorMenu::SelectColorPane(ColorPane *pane)
{
    for (auto colorPane : colorPanes)
    {
        colorPane->selected = (colorPane == pane);
        colorPane->Refresh();
    }
    selectedColorPane = pane;
    MyApp::GetStrokeSettings().color = pane->color;
}

void ColorMenu::SelectCustomColor(wxWindow *parent)
{
    wxColourData data;
    data.SetChooseFull(true);
    for (int i = 0; i < 16; ++i)
    {
        wxColour color(i * 16, i * 16, i * 16);
        data.SetCustomColour(i, color);
    }
    wxColourDialog dialog(parent, &data);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxColourData retData = dialog.GetColourData();
        wxColour col = retData.GetColour();
        MyApp::GetStrokeSettings().color = col;
        selectedColorPane->color = col;
        selectedColorPane->Refresh();
    }
}
