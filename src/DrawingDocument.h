#pragma once

#include <wx/docview.h>
#include <wx/stdstream.h>
#include <iostream>
#include "Shape/Path.h"
#include "Shape/Shape.h"

class DrawingDocument : public wxDocument
{
public:
    std::ostream &SaveObject(std::ostream &stream) override;
    std::istream &LoadObject(std::istream &stream) override;

public:
    std::vector<Path> lines{};
    std::vector<Shape> shapes{};
    wxDECLARE_DYNAMIC_CLASS(DrawingDocument);
};