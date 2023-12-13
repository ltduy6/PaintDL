#include "DrawingDocument.h"
#include "Helper/StreamUtils.h"

wxIMPLEMENT_DYNAMIC_CLASS(DrawingDocument, wxDocument);

std::ostream &DrawingDocument::SaveObject(std::ostream &stream)
{
    auto doc = serializer.SerializeCanvasObjects(objects);

    auto wrapper = OStreamWrapper(stream);
    serializer.CompressXml(doc, wrapper);

    return stream;
}

std::istream &DrawingDocument::LoadObject(std::istream &stream)
{
    auto wrapper = IStreamWrapper(stream);
    auto doc = serializer.DecompressXml(wrapper);

    objects = serializer.DeserializeCanvasObjects(doc);
    auto m_shape = objects.begin()->get().GetShape();
    if (std::holds_alternative<Path>(m_shape))
    {
        std::cout << "path" << std::endl;
    }
    else if (std::holds_alternative<Rect>(m_shape))
    {
        std::cout << "rect" << std::endl;
    }
    else if (std::holds_alternative<Circle>(m_shape))
    {
        std::cout << "circle" << std::endl;
    }
    else if (std::holds_alternative<ITriangle>(m_shape))
    {
        std::cout << "itriangle" << std::endl;
    }
    else if (std::holds_alternative<RTriangle>(m_shape))
    {
        std::cout << "rtriangle" << std::endl;
    }
    else if (std::holds_alternative<Diamond>(m_shape))
    {
        std::cout << "diamond" << std::endl;
    }
    else if (std::holds_alternative<Text>(m_shape))
    {
        std::cout << "text" << std::endl;
    }
    else
    {
        std::cout << "unknown" << std::endl;
    }
    stream.clear();
    return stream;
}
