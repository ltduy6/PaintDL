#pragma once

#include "ColorPane.h"
#include "RoundedButton.h"
#include "../MyApp.h"

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>
#include <wx/colordlg.h>

class ColorMenu
{
public:
    void SetUpColorMenu(wxWindow *parent, wxSizer *size, wxFrame *frame);

private:
    void SelectColorPane(ColorPane *pane);
    void SelectCustomColor(wxWindow *parent);

private:
    ColorPane *selectedColorPane;
    std::vector<ColorPane *> colorPanes;
    const std::vector<std::string> niceColors = {"#000000", "#ffffff", "#fd7f6f",
                                                 "#7eb0d5", "#b2e061", "#bd7ebe",
                                                 "#ffb55a", "#ffee65", "#beb9db",
                                                 "#fdcce5", "#8bd3c7"};
};