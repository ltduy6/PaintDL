#include "SizeMenu.h"

void SizeMenu::SetUpSizeMenu(wxWindow *parent, wxSizer *sizer)
{
    for (const auto &i : penWidths)
    {
        auto sizePane = new SizePane(parent, wxID_ANY, i);

        sizePane->Bind(wxEVT_LEFT_DOWN, [this, sizePane](wxMouseEvent &event)
                       { SelectSizePane(sizePane); });

        sizePanes.push_back(sizePane);
        sizer->Add(sizePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }
    SelectSizePane(sizePanes[2]);
}

void SizeMenu::SelectSizePane(SizePane *pane)
{
    for (auto sizePane : sizePanes)
    {
        sizePane->selected = (sizePane == pane);
        sizePane->Refresh();
    }
    MyApp::GetStrokeSettings().width = pane->width;
}
