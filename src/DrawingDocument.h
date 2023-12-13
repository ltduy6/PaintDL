#pragma once

#include <wx/docview.h>
#include <wx/stdstream.h>

#include <iostream>

#include "xmlSerializer.h"
#include "Canvas/CanvasObject.h"

class DrawingDocument : public wxDocument
{
public:
    std::ostream &SaveObject(std::ostream &stream) override;
    std::istream &LoadObject(std::istream &stream) override;

public:
    std::vector<std::reference_wrapper<CanvasObject>> objects{};
    XmlSerializer serializer{};
    wxDECLARE_DYNAMIC_CLASS(DrawingDocument);
};