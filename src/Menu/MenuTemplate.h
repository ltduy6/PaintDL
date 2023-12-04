#pragma once

#include <wx/wx.h>
#include <wx/wrapsizer.h>

class MenuTemplate
{
public:
    void Show(bool show = true);

protected:
    wxWindow *m_parent;
    wxSizer *m_sizer;
    wxStaticText *m_text;
};