#include "MenuTemplate.h"

void MenuTemplate::Show(bool show)
{
    if (show)
    {
        for (auto &item : m_sizer->GetChildren())
        {
            item->GetWindow()->Enable();
        }
    }
    else
    {
        for (auto &item : m_sizer->GetChildren())
        {
            item->GetWindow()->Disable();
        }
    }
    m_parent->Layout();
}