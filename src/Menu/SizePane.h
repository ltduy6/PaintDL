#include "SelectablePane.h"
class SizePane : public SelectablePane
{
public:
    SizePane(wxWindow *parent, wxWindowID id, int width, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    int width{3};

private:
    virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
};