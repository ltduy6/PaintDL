#pragma once

#include "SizePane.h"
#include "../MyApp.h"
#include "MenuTemplate.h"
#include <vector>

class SizeMenu : public MenuTemplate
{
public:
    void SetUpSizeMenu(wxWindow *parent, wxSizer *sizer, std::string labelText);

private:
    void UpdateWidth(const int &width, const std::string &label);
    void SetUpFontSizeMenu(wxWindow *parent, wxSizer *sizer);
    void SetUpShapeMenu(wxWindow *parent, wxSizer *sizer, const std::string &labelText);

private:
    wxSlider *slider;
    wxComboBox *comboBox;
};