#include "FontMenu.h"

void FontMenu::SetUpFontMenu(wxWindow *parent, wxSizer *sizer)
{
    auto m_label = new wxStaticText(parent, wxID_ANY, "Font");
    m_label->SetForegroundColour(wxColour(231, 246, 242));
    sizer->Add(m_label, 0, wxALL, parent->FromDIP(5));

    wxWrapSizer *wrapSizer = new wxWrapSizer(wxHORIZONTAL);
    auto font = new ToolsPane(parent, wxID_ANY, ToolType::Font);
    font->AddCallback([this, parent]()
                      { SelectFont(parent); });
    wrapSizer->Add(font, 0, wxRIGHT | wxBOTTOM, parent->FromDIP(5));

    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_parent = parent;
    m_sizer = wrapSizer;
    m_text = m_label;
}

void FontMenu::SelectFont(wxWindow *parent)
{
    wxFontData data;
    data.SetInitialFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    wxFontDialog dialog(parent, data);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxFontData retData = dialog.GetFontData();
        wxFont font = retData.GetChosenFont();
        MyApp::GetStrokeSettings().font = font;
    }
}
