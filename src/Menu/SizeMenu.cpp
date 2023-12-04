#include "SizeMenu.h"

void SizeMenu::SetUpSizeMenu(wxWindow *parent, wxSizer *sizer)
{
    auto wrapSizer = new wxWrapSizer(wxHORIZONTAL);
    auto label = new wxStaticText(parent, wxID_ANY, "Size");
    label->SetForegroundColour(wxColour(231, 246, 242));

    for (const auto &i : penWidths)
    {
        auto sizePane = new SizePane(parent, wxID_ANY, i);

        sizePane->AddCallback([this, sizePane]()
                              { SelectSizePane(sizePane); });

        sizePanes.push_back(sizePane);
        wrapSizer->Add(sizePane, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));
    }
    SelectSizePane(sizePanes[2]);

    sizer->Add(label, 0, wxALL, parent->FromDIP(5));
    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_parent = parent;
    m_sizer = wrapSizer;
    m_text = label;
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
