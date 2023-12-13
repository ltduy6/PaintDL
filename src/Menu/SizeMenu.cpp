#include "SizeMenu.h"

void SizeMenu::SetUpSizeMenu(wxWindow *parent, wxSizer *sizer, std::string labelTex)
{
    if (labelTex == "Font size")
        SetUpFontSizeMenu(parent, sizer);
    else
        SetUpShapeMenu(parent, sizer, labelTex);
}

void SizeMenu::UpdateWidth(const int &width, const std::string &label)
{
    if (label == "Outline Size")
        MyApp::GetStrokeSettings().outlineWidth = width;
    else if (label == "Size")
        MyApp::GetStrokeSettings().width = width;
    else if (label == "Font size")
        MyApp::GetStrokeSettings().fontSize = width;
}

void SizeMenu::SetUpFontSizeMenu(wxWindow *parent, wxSizer *sizer)
{
    auto wrapSizer = new wxWrapSizer(wxHORIZONTAL);
    auto label = new wxStaticText(parent, wxID_ANY, "Font size");
    label->SetForegroundColour(wxColour(231, 246, 242));

    comboBox = new wxComboBox(parent, wxID_ANY, "10 pt", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
    comboBox->Append("8 pt");
    comboBox->Append("10 pt");
    comboBox->Append("12 pt");
    comboBox->Append("14 pt");
    comboBox->Append("18 pt");
    comboBox->Append("24 pt");
    comboBox->Append("36 pt");
    comboBox->Append("48 pt");
    comboBox->Append("60 pt");
    comboBox->Append("72 pt");

    comboBox->SetSelection(1);

    comboBox->Bind(wxEVT_COMBOBOX, [&](wxCommandEvent &event)
                   { UpdateWidth(std::stoi(event.GetString().ToStdString()), "Font size"); });

    wrapSizer->Add(comboBox, 0, wxALL, parent->FromDIP(5));

    sizer->Add(label, 0, wxALL, parent->FromDIP(5));
    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_parent = parent;
    m_sizer = wrapSizer;
    m_text = label;
}

void SizeMenu::SetUpShapeMenu(wxWindow *parent, wxSizer *sizer, const std::string &labelText)
{
    auto wrapSizer = new wxWrapSizer(wxHORIZONTAL);
    auto label = new wxStaticText(parent, wxID_ANY, labelText);
    label->SetForegroundColour(wxColour(231, 246, 242));

    slider = new wxSlider(parent, wxID_ANY, 3, 1, 28, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    slider->SetForegroundColour(wxColour(231, 246, 242));
    slider->SetBackgroundStyle(wxBG_STYLE_PAINT);

    slider->Bind(wxEVT_SLIDER, [&, labelText](wxCommandEvent &event)
                 { UpdateWidth(event.GetInt(), labelText); });

    wrapSizer->Add(slider, 0, wxALL, parent->FromDIP(5));

    sizer->Add(label, 0, wxALL, parent->FromDIP(5));
    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_parent = parent;
    m_sizer = wrapSizer;
    m_text = label;
}
