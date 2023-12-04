#pragma once

#include "ToolMenu.h"
#include "MenuTemplate.h"
#include <wx/combobox.h>
#include <wx/wrapsizer.h>

class ZoomToolMenu : public ToolMenu, public MenuTemplate
{
public:
    ZoomToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer);
    virtual void ShowMenu(bool show) override;
    ~ZoomToolMenu() = default;

private:
    wxComboBox *zoomComboBox;
    wxWindow *parent;
};