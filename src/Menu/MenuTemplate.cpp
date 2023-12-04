#include "MenuTemplate.h"

void MenuTemplate::Show(bool show)
{
    if (show)
    {
        m_parent->GetSizer()->Show(m_sizer);
        m_parent->GetSizer()->Show(m_text);
    }
    else
    {
        m_parent->GetSizer()->Hide(m_sizer);
        m_parent->GetSizer()->Hide(m_text);
    }
    m_parent->Layout();
}