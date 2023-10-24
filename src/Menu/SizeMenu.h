#include "SelectableMenu.h"
class SizeMenu : public SelectableMenu
{
public:
    SizeMenu(wxWindow *parent, wxWindowID id, int width, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    int width;

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
};