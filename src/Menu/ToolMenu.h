#pragma once

#include "../MyApp.h"
#include "ToolsPane.h"

#include <functional>

class ToolMenu
{
public:
    ToolMenu(wxWindow *parent, wxSizer *sizer, ToolType type);
    void Show(bool show);
    virtual ~ToolMenu() = default;
    void SetCallback(std::function<void()> callback);

protected:
    virtual void ShowMenu(bool show) = 0;

public:
    ToolType type;

private:
    ToolsPane *mainToolPane;
};