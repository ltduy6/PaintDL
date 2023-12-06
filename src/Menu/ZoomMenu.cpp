#include "ZoomMenu.h"
#include <sstream>
#include <iomanip>

void ZoomMenu::SetUpZoomMenu(wxWindow *parent, wxSizer *sizer)
{
    auto wrapSizer = new wxBoxSizer(wxHORIZONTAL);
    auto label = new wxStaticText(parent, wxID_ANY, "Zoom Level:");
    label->SetForegroundColour(wxColour(231, 246, 242));

    zoomComboBox = new wxComboBox(parent, wxID_ANY, "100%", wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_DROPDOWN);
    zoomComboBox->SetForegroundColour(wxColour(231, 246, 242));
    zoomComboBox->SetBackgroundColour(wxColour(83, 83, 83));

    zoomComboBox->Append("50%");
    zoomComboBox->Append("100%");
    zoomComboBox->Append("150%");
    zoomComboBox->Append("200%");
    zoomComboBox->Append("250%");
    zoomComboBox->Append("300%");
    zoomComboBox->Append("350%");
    zoomComboBox->Append("400%");

    zoomComboBox->SetSelection(1);

    wrapSizer->Add(zoomComboBox, 0, wxALL, parent->FromDIP(5));

    sizer->Add(label, 0, wxALL, parent->FromDIP(5));
    sizer->Add(wrapSizer, 0, wxALL, parent->FromDIP(5));

    m_sizer = wrapSizer;
    m_text = label;
    m_parent = parent;
}

void ZoomMenu::UpdateCanvasZoom(DrawingCanvas *drawingCanvas)
{
    zoomComboBox->Bind(wxEVT_COMBOBOX, [drawingCanvas](wxCommandEvent &event)
                       {
                           auto zoom = event.GetString();
                            if (zoom == "50%")
                               drawingCanvas->Zoom(0.5);
                           else if (zoom == "100%")
                               drawingCanvas->Zoom(1);
                           else if (zoom == "150%")
                               drawingCanvas->Zoom(1.5);
                           else if (zoom == "200%")
                               drawingCanvas->Zoom(2);
                            else if (zoom == "250%")
                               drawingCanvas->Zoom(2.5);
                            else if (zoom == "300%")
                               drawingCanvas->Zoom(3);
                            else if (zoom == "350%")
                               drawingCanvas->Zoom(3.5);
                            else if (zoom == "400%")
                               drawingCanvas->Zoom(4); });
}

void ZoomMenu::UpdateZoomComboBox(double zoomFactor)
{
    zoomFactor = std::ceil(zoomFactor * 100.0) / 100.0;

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(0) << zoomFactor * 100;
    std::string str = stream.str() + "%";

    zoomComboBox->SetValue(str);
}
