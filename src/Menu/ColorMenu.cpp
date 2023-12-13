#include "ColorMenu.h"

void ColorMenu::SetUpColorMenu(wxWindow *parent, wxSizer *sizer, int numColorPanes, std::string label)
{
    auto m_label = new wxStaticText(parent, wxID_ANY, label);
    m_label->SetForegroundColour(wxColour(231, 246, 242));
    sizer->Add(m_label, 0, wxALL, parent->FromDIP(5));

    auto wrapSizer = new wxWrapSizer(wxHORIZONTAL);

    if (label == "Fill")
    {
        auto colorPane = new ColorPane(parent, wxID_ANY, *wxWHITE);
        colorPane->AddCallback([this, colorPane, label]()
                               { SelectColorPane(colorPane, label); });
        colorPanes.push_back(colorPane);
        wrapSizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));

        auto customColor = new ToolsPane(parent, wxID_ANY, ToolType::CustomColor);
        customColor->AddCallback([this, parent, label]()
                                 { SelectCustomColor(parent, label); });
        wrapSizer->Add(customColor, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));

        auto gradient = new ToolsPane(parent, wxID_ANY, ToolType::Gradient);
        gradient->AddCallback([this]()
                              { SelectGradient(); });
        wrapSizer->Add(gradient, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));

        auto noFill = new ToolsPane(parent, wxID_ANY, ToolType::NoFill);
        noFill->AddCallback([this]()
                            { UpdateColor(wxTransparentColour, "Fill");
                            selectedColorPane->SetSingleColour(wxTransparentColour);
                            selectedColorPane->Refresh(); });
        wrapSizer->Add(noFill, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }

    if (label == "Outline")
    {
        auto colorPane = new ColorPane(parent, wxID_ANY, wxColour(niceColors[0]));
        colorPane->AddCallback([this, colorPane, label]()
                               { SelectColorPane(colorPane, label); });
        colorPanes.push_back(colorPane);
        wrapSizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));

        auto customColor = new ToolsPane(parent, wxID_ANY, ToolType::CustomColor);
        customColor->AddCallback([this, parent, label]()
                                 { SelectCustomColor(parent, label); });
        wrapSizer->Add(customColor, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }

    if (label == "Color")
    {
        for (int i = 0; i < numColorPanes; ++i)
        {
            auto colorPane = new ColorPane(parent, wxID_ANY, wxColour(niceColors[i]));
            colorPane->AddCallback([this, colorPane, label]()
                                   { SelectColorPane(colorPane, label); });
            colorPanes.push_back(colorPane);
            wrapSizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
        }

        auto customColor = new ToolsPane(parent, wxID_ANY, ToolType::CustomColor);
        customColor->AddCallback([this, parent, label]()
                                 { SelectCustomColor(parent, label); });
        wrapSizer->Add(customColor, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }

    SelectColorPane(colorPanes[0], label);

    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_parent = parent;
    m_sizer = wrapSizer;
    m_text = m_label;
}

void ColorMenu::ResetColorMenu()
{
    for (auto colorPane : colorPanes)
    {
        colorPane->selected = false;
        colorPane->Refresh();
    }
}

void ColorMenu::AddCallback(std::function<void()> callback)
{
    for (auto colorPane : colorPanes)
        colorPane->AddCallback(callback);
}

void ColorMenu::SelectColorPane(ColorPane *pane, std::string label)
{
    for (auto colorPane : colorPanes)
    {
        colorPane->selected = (colorPane == pane);
        colorPane->Refresh();
    }
    selectedColorPane = pane;
    UpdateColor(pane->color, label);
}

void ColorMenu::SelectCustomColor(wxWindow *parent, std::string label)
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
        UpdateColor(col, label);
        selectedColorPane->SetSingleColour(col);
        selectedColorPane->Refresh();
    }
}

void ColorMenu::UpdateColor(wxColour colour, std::string label)
{
    if (label == "Color")
        MyApp::GetStrokeSettings().color = colour;
    else if (label == "Outline")
        MyApp::GetStrokeSettings().outlineColor = colour;
    else if (label == "Fill")
    {
        MyApp::GetStrokeSettings().fillColor = colour;
        MyApp::GetStrokeSettings().isGradient = false;
    }
}

void ColorMenu::SelectGradient()
{
    wxGradientDialog *dialog = new wxGradientDialog(m_parent);
    if (dialog->ShowModal() == wxID_OK)
    {
        wxGraphicsGradientStops *stops = new wxGraphicsGradientStops();
        for (int i = 0; i < dialog->GetGradient().getMax(); ++i)
        {
            stops->Add(dialog->GetGradient().getColorAt(i), i / (double)dialog->GetGradient().getMax());
        }
        MyApp::GetStrokeSettings().gradientStops = *stops;
        MyApp::GetStrokeSettings().isGradient = true;
        selectedColorPane->SetGradientColour(*stops);
        selectedColorPane->Refresh();
        delete stops;
    }
    delete dialog;
}
