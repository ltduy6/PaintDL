#include "HistoryPane.h"

HistoryPane::HistoryPane(wxWindow *parent, wxString name, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size), name(name)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &HistoryPane::OnPaint, this);
}

void HistoryPane::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(this->GetParent()->GetBackgroundColour()));
    dc.Clear();

    auto gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        wxRect contentRect{0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight()};
        gc->SetBrush(wxBrush(wxColour(89, 90, 90)));
        gc->DrawRectangle(contentRect.GetX(), contentRect.GetY(), contentRect.GetWidth(), contentRect.GetHeight());

        gc->SetPen(wxColour(WHITE_PEN));
        wxFont font(wxFontInfo(FromDIP(5)).Family(wxFONTFAMILY_DEFAULT).FaceName("Segoe UI"));
        gc->SetFont(font, wxColour(WHITE_PEN));
        wxDouble *width = new wxDouble;
        wxDouble *height = new wxDouble;
        gc->GetTextExtent(name, width, height);
        gc->DrawText(name, contentRect.GetX() + (contentRect.GetWidth() - *width) / 2, contentRect.GetY() + (contentRect.GetHeight() - *height) / 2);
    }
}
