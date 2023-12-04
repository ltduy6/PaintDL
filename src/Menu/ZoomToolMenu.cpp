#include "ZoomToolMenu.h"

ZoomToolMenu::ZoomToolMenu(wxWindow *parent, wxSizer *sizer, wxWindow *toolParent, wxSizer *toolSizer) : ToolMenu(toolParent, toolSizer, ToolType::ZoomIn), parent(parent)
{
    auto label = new wxStaticText(parent, wxID_ANY, "Predefined zoom:");
    label->SetForegroundColour(wxColour(231, 246, 242));
    sizer->Add(label, 0, wxALL, parent->FromDIP(5));

    auto wrapSizer = new wxWrapSizer(wxHORIZONTAL);
    wxComboBox *zoomBox = new wxComboBox(parent, wxID_ANY, "100%", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
    zoomBox->Append("25%");
    zoomBox->Append("50%");
    zoomBox->Append("75%");
    zoomBox->Append("100%");
    zoomBox->Append("125%");
    zoomBox->Append("150%");
    zoomBox->Append("175%");
    zoomBox->Append("200%");
    zoomBox->SetSelection(3);
    wrapSizer->Add(zoomBox, 0, wxALL, parent->FromDIP(5));
    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_parent = parent;
    m_sizer = wrapSizer;
    m_text = label;
}

void ZoomToolMenu::ShowMenu(bool show)
{
    MenuTemplate::Show(show);
}
