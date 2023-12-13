#pragma once

#include "ColorPane.h"
#include "ToolsPane.h"
#include "../MyApp.h"
#include "MenuTemplate.h"
#include "../Gradient/gradientdlg.h"

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/colordlg.h>
#include <wx/generic/colrdlgg.h>

class ColorMenu : public MenuTemplate
{
public:
    void SetUpColorMenu(wxWindow *parent, wxSizer *sizer, int numColorPanes = 11, std::string label = "Color");
    void ResetColorMenu();
    void AddCallback(std::function<void()> callback);

private:
    void SelectColorPane(ColorPane *pane, std::string label);
    void SelectCustomColor(wxWindow *parent, std::string label);
    void UpdateColor(wxColour colour, std::string label);
    void SelectGradient();
    void SetUpOutlineMenu(wxWindow *parent, wxSizer *sizer, int numColorPanes = 11, std::string label = "Outline");
    void SetUpFillMenu(wxWindow *parent, wxSizer *sizer, int numColorPanes = 11, std::string label = "Fill");

private:
    ColorPane *selectedColorPane;
    std::vector<ColorPane *> colorPanes;
    const std::vector<std::string> niceColors = {"#000000", "#ffffff", "#fd7f6f",
                                                 "#7eb0d5", "#b2e061", "#bd7ebe",
                                                 "#ffb55a", "#ffee65", "#beb9db",
                                                 "#fdcce5", "#8bd3c7"};
};