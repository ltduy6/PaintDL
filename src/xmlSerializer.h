#pragma once

#include <wx/xml/xml.h>
#include <wx/fs_zip.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>

#include <memory>

#include "Shape/Shape.h"
#include "Canvas/CanvasObject.h"
#include "Transform/Transformation.h"

namespace XmlNodeKeys
{
    constexpr auto ObjectNodeName = "Object";
    constexpr auto PathNodeType = "Path";
    constexpr auto RectNodeType = "Rect";
    constexpr auto CircleNodeType = "Circle";
    constexpr auto ITriangleNodeType = "ITriangle";
    constexpr auto RTriangleNodeType = "RTriangle";
    constexpr auto DiamondNodeType = "Diamond";
    constexpr auto TextNodeType = "Text";

    constexpr auto RectElementNodeName = "Rect";
    constexpr auto PointElementNodeName = "Point";
    constexpr auto TextElementNodeName = "Text";

    constexpr auto ColorAttribute = "Color";
    constexpr auto OutlineColorAttribute = "OutlineColor";
    constexpr auto FillColorAttribute = "FillColor";
    constexpr auto TextColorAttribute = "TextColor";
    constexpr auto WidthAttribute = "Width";
    constexpr auto HeightAttribute = "Height";
    constexpr auto XAttribute = "X";
    constexpr auto YAttribute = "Y";
    constexpr auto TextAttribute = "text";
    constexpr auto TypeAttribute = "type";

    constexpr auto TransformationNodeName = "Transformation";
    constexpr auto ScaleXAttribute = "scaleX";
    constexpr auto ScaleYAttribute = "scaleY";
    constexpr auto RotationAttribute = "rotation";
    constexpr auto TranslationXAttribute = "translationX";
    constexpr auto TranslationYAttribute = "translationY";

    constexpr auto DocumentNodeName = "PaintDocument";
    constexpr auto VersionAttribute = "Version";
    constexpr auto VersionValue = "1.2";
};

struct XmlSerializingVisitor
{
    wxXmlNode *objectNode;

    void operator()(const Rect &rect)
    {
        objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::ObjectNodeName);

        objectNode->AddAttribute(XmlNodeKeys::TypeAttribute, XmlNodeKeys::RectNodeType);
        objectNode->AddAttribute(XmlNodeKeys::OutlineColorAttribute, rect.outlineColor.GetAsString(wxC2S_HTML_SYNTAX));
        objectNode->AddAttribute(XmlNodeKeys::FillColorAttribute, rect.fillColor.GetAsString(wxC2S_HTML_SYNTAX));

        wxXmlNode *rectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::RectElementNodeName);
        rectNode->AddAttribute(XmlNodeKeys::XAttribute, wxString::FromDouble(rect.rect.m_x));
        rectNode->AddAttribute(XmlNodeKeys::YAttribute, wxString::FromDouble(rect.rect.m_y));
        rectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(rect.rect.m_width));
        rectNode->AddAttribute(XmlNodeKeys::HeightAttribute, wxString::FromDouble(rect.rect.m_height));

        objectNode->AddChild(rectNode);
    }
    void operator()(const Path &path)
    {
        objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::ObjectNodeName);

        objectNode->AddAttribute(XmlNodeKeys::TypeAttribute, XmlNodeKeys::PathNodeType);
        objectNode->AddAttribute(XmlNodeKeys::ColorAttribute, path.color.GetAsString(wxC2S_HTML_SYNTAX));
        objectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(path.width));

        for (const auto &point : path.points)
        {
            wxXmlNode *pointNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::PointElementNodeName);
            pointNode->AddAttribute(XmlNodeKeys::XAttribute, wxString::FromDouble(point.m_x));
            pointNode->AddAttribute(XmlNodeKeys::YAttribute, wxString::FromDouble(point.m_y));
            objectNode->AddChild(pointNode);
        }
    }
    void operator()(const Circle &circle)
    {
        objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::ObjectNodeName);

        objectNode->AddAttribute(XmlNodeKeys::TypeAttribute, XmlNodeKeys::CircleNodeType);
        objectNode->AddAttribute(XmlNodeKeys::OutlineColorAttribute, circle.outlineColor.GetAsString(wxC2S_HTML_SYNTAX));
        objectNode->AddAttribute(XmlNodeKeys::FillColorAttribute, circle.fillColor.GetAsString(wxC2S_HTML_SYNTAX));

        wxXmlNode *rectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::RectElementNodeName);
        rectNode->AddAttribute(XmlNodeKeys::XAttribute, wxString::FromDouble(circle.rect.m_x));
        rectNode->AddAttribute(XmlNodeKeys::YAttribute, wxString::FromDouble(circle.rect.m_y));
        rectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(circle.rect.m_width));
        rectNode->AddAttribute(XmlNodeKeys::HeightAttribute, wxString::FromDouble(circle.rect.m_height));

        objectNode->AddChild(rectNode);
    }
    void operator()(const ITriangle &triangle)
    {
        objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::ObjectNodeName);

        objectNode->AddAttribute(XmlNodeKeys::TypeAttribute, XmlNodeKeys::ITriangleNodeType);
        objectNode->AddAttribute(XmlNodeKeys::OutlineColorAttribute, triangle.outlineColor.GetAsString(wxC2S_HTML_SYNTAX));
        objectNode->AddAttribute(XmlNodeKeys::FillColorAttribute, triangle.fillColor.GetAsString(wxC2S_HTML_SYNTAX));

        wxXmlNode *rectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::RectElementNodeName);
        rectNode->AddAttribute(XmlNodeKeys::XAttribute, wxString::FromDouble(triangle.rect.m_x));
        rectNode->AddAttribute(XmlNodeKeys::YAttribute, wxString::FromDouble(triangle.rect.m_y));
        rectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(triangle.rect.m_width));
        rectNode->AddAttribute(XmlNodeKeys::HeightAttribute, wxString::FromDouble(triangle.rect.m_height));

        objectNode->AddChild(rectNode);
    }
    void operator()(const RTriangle &triangle)
    {
        objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::ObjectNodeName);

        objectNode->AddAttribute(XmlNodeKeys::TypeAttribute, XmlNodeKeys::RTriangleNodeType);
        objectNode->AddAttribute(XmlNodeKeys::OutlineColorAttribute, triangle.outlineColor.GetAsString(wxC2S_HTML_SYNTAX));
        objectNode->AddAttribute(XmlNodeKeys::FillColorAttribute, triangle.fillColor.GetAsString(wxC2S_HTML_SYNTAX));

        wxXmlNode *rectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::RectElementNodeName);
        rectNode->AddAttribute(XmlNodeKeys::XAttribute, wxString::FromDouble(triangle.rect.m_x));
        rectNode->AddAttribute(XmlNodeKeys::YAttribute, wxString::FromDouble(triangle.rect.m_y));
        rectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(triangle.rect.m_width));
        rectNode->AddAttribute(XmlNodeKeys::HeightAttribute, wxString::FromDouble(triangle.rect.m_height));

        objectNode->AddChild(rectNode);
    }
    void operator()(const Diamond &diamond)
    {
        objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::ObjectNodeName);

        objectNode->AddAttribute(XmlNodeKeys::TypeAttribute, XmlNodeKeys::DiamondNodeType);
        objectNode->AddAttribute(XmlNodeKeys::OutlineColorAttribute, diamond.outlineColor.GetAsString(wxC2S_HTML_SYNTAX));
        objectNode->AddAttribute(XmlNodeKeys::FillColorAttribute, diamond.fillColor.GetAsString(wxC2S_HTML_SYNTAX));

        wxXmlNode *rectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::RectElementNodeName);
        rectNode->AddAttribute(XmlNodeKeys::XAttribute, wxString::FromDouble(diamond.rect.m_x));
        rectNode->AddAttribute(XmlNodeKeys::YAttribute, wxString::FromDouble(diamond.rect.m_y));
        rectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(diamond.rect.m_width));
        rectNode->AddAttribute(XmlNodeKeys::HeightAttribute, wxString::FromDouble(diamond.rect.m_height));

        objectNode->AddChild(rectNode);
    }
    void operator()(const Text &text)
    {
        objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::ObjectNodeName);

        objectNode->AddAttribute(XmlNodeKeys::TypeAttribute, XmlNodeKeys::TextNodeType);
        objectNode->AddAttribute(XmlNodeKeys::TextColorAttribute, text.color.GetAsString(wxC2S_HTML_SYNTAX));
        objectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(text.width));
        objectNode->AddAttribute(XmlNodeKeys::TextAttribute, text.text);

        wxXmlNode *rectNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::RectElementNodeName);
        rectNode->AddAttribute(XmlNodeKeys::XAttribute, wxString::FromDouble(text.rect.m_x));
        rectNode->AddAttribute(XmlNodeKeys::YAttribute, wxString::FromDouble(text.rect.m_y));
        rectNode->AddAttribute(XmlNodeKeys::WidthAttribute, wxString::FromDouble(text.rect.m_width));
        rectNode->AddAttribute(XmlNodeKeys::HeightAttribute, wxString::FromDouble(text.rect.m_height));

        objectNode->AddChild(rectNode);
    }
};

struct XmlDeserializingShapeFactory
{
    Shape Deserialize(const wxXmlNode *node)
    {
        auto type = node->GetAttribute(XmlNodeKeys::TypeAttribute);
        if (type == XmlNodeKeys::PathNodeType)
            return DeserializePath(node);
        else if (type == XmlNodeKeys::RectNodeType)
            return DeserializeRect(node);
        else if (type == XmlNodeKeys::CircleNodeType)
            return DeserializeCircle(node);
        else if (type == XmlNodeKeys::ITriangleNodeType)
            return DeserializeITriangle(node);
        else if (type == XmlNodeKeys::RTriangleNodeType)
            return DeserializeRTriangle(node);
        else if (type == XmlNodeKeys::DiamondNodeType)
            return DeserializeDiamond(node);
        else if (type == XmlNodeKeys::TextNodeType)
            return DeserializeText(node);

        throw std::runtime_error("Unknown shape type");
    }

private:
    Rect DeserializeRect(const wxXmlNode *node)
    {
        Rect object;
        object.outlineColor.Set(node->GetAttribute(XmlNodeKeys::OutlineColorAttribute));
        object.fillColor.Set(node->GetAttribute(XmlNodeKeys::FillColorAttribute));

        const wxXmlNode *rectNode = node->GetChildren();
        object.rect.m_x = wxAtof(rectNode->GetAttribute(XmlNodeKeys::XAttribute));
        object.rect.m_y = wxAtof(rectNode->GetAttribute(XmlNodeKeys::YAttribute));
        object.rect.m_width = wxAtof(rectNode->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.rect.m_height = wxAtof(rectNode->GetAttribute(XmlNodeKeys::HeightAttribute));

        return object;
    }
    Path DeserializePath(const wxXmlNode *node)
    {
        Path object;
        object.color.Set(node->GetAttribute(XmlNodeKeys::ColorAttribute));
        object.width = wxAtof(node->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.points = {};

        for (wxXmlNode *pointNode = node->GetChildren(); pointNode != nullptr; pointNode = pointNode->GetNext())
        {
            if (pointNode->GetName() != XmlNodeKeys::PointElementNodeName)
                continue;
            wxPoint2DDouble point;
            point.m_x = wxAtof(pointNode->GetAttribute(XmlNodeKeys::XAttribute));
            point.m_y = wxAtof(pointNode->GetAttribute(XmlNodeKeys::YAttribute));
            object.points.push_back(point);
        }

        return object;
    }
    Circle DeserializeCircle(const wxXmlNode *node)
    {
        Circle object;
        object.outlineColor.Set(node->GetAttribute(XmlNodeKeys::OutlineColorAttribute));
        object.fillColor.Set(node->GetAttribute(XmlNodeKeys::FillColorAttribute));

        const wxXmlNode *rectNode = node->GetChildren();
        object.rect.m_x = wxAtof(rectNode->GetAttribute(XmlNodeKeys::XAttribute));
        object.rect.m_y = wxAtof(rectNode->GetAttribute(XmlNodeKeys::YAttribute));
        object.rect.m_width = wxAtof(rectNode->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.rect.m_height = wxAtof(rectNode->GetAttribute(XmlNodeKeys::HeightAttribute));

        return object;
    }
    ITriangle DeserializeITriangle(const wxXmlNode *node)
    {
        ITriangle object;
        object.outlineColor.Set(node->GetAttribute(XmlNodeKeys::OutlineColorAttribute));
        object.fillColor.Set(node->GetAttribute(XmlNodeKeys::FillColorAttribute));

        const wxXmlNode *rectNode = node->GetChildren();
        object.rect.m_x = wxAtof(rectNode->GetAttribute(XmlNodeKeys::XAttribute));
        object.rect.m_y = wxAtof(rectNode->GetAttribute(XmlNodeKeys::YAttribute));
        object.rect.m_width = wxAtof(rectNode->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.rect.m_height = wxAtof(rectNode->GetAttribute(XmlNodeKeys::HeightAttribute));

        return object;
    }
    RTriangle DeserializeRTriangle(const wxXmlNode *node)
    {
        RTriangle object;
        object.outlineColor.Set(node->GetAttribute(XmlNodeKeys::OutlineColorAttribute));
        object.fillColor.Set(node->GetAttribute(XmlNodeKeys::FillColorAttribute));

        const wxXmlNode *rectNode = node->GetChildren();
        object.rect.m_x = wxAtof(rectNode->GetAttribute(XmlNodeKeys::XAttribute));
        object.rect.m_y = wxAtof(rectNode->GetAttribute(XmlNodeKeys::YAttribute));
        object.rect.m_width = wxAtof(rectNode->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.rect.m_height = wxAtof(rectNode->GetAttribute(XmlNodeKeys::HeightAttribute));

        return object;
    }
    Diamond DeserializeDiamond(const wxXmlNode *node)
    {
        Diamond object;
        object.outlineColor.Set(node->GetAttribute(XmlNodeKeys::OutlineColorAttribute));
        object.fillColor.Set(node->GetAttribute(XmlNodeKeys::FillColorAttribute));

        const wxXmlNode *rectNode = node->GetChildren();
        object.rect.m_x = wxAtof(rectNode->GetAttribute(XmlNodeKeys::XAttribute));
        object.rect.m_y = wxAtof(rectNode->GetAttribute(XmlNodeKeys::YAttribute));
        object.rect.m_width = wxAtof(rectNode->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.rect.m_height = wxAtof(rectNode->GetAttribute(XmlNodeKeys::HeightAttribute));

        return object;
    }
    Text DeserializeText(const wxXmlNode *node)
    {
        Text object;
        object.color.Set(node->GetAttribute(XmlNodeKeys::TextColorAttribute));
        object.width = wxAtof(node->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.text = node->GetAttribute(XmlNodeKeys::TextAttribute);

        const wxXmlNode *rectNode = node->GetChildren();
        object.rect.m_x = wxAtof(rectNode->GetAttribute(XmlNodeKeys::XAttribute));
        object.rect.m_y = wxAtof(rectNode->GetAttribute(XmlNodeKeys::YAttribute));
        object.rect.m_width = wxAtof(rectNode->GetAttribute(XmlNodeKeys::WidthAttribute));
        object.rect.m_height = wxAtof(rectNode->GetAttribute(XmlNodeKeys::HeightAttribute));

        return object;
    }
};

struct XmlSerializer
{
    XmlSerializer()
    {
        wxFileSystem::AddHandler(new wxZipFSHandler);
    }

    wxXmlDocument SerializeCanvasObjects(const std::vector<std::reference_wrapper<CanvasObject>> &objects)
    {
        wxXmlDocument doc;

        wxXmlNode *docNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::DocumentNodeName);
        docNode->AddAttribute(XmlNodeKeys::VersionAttribute, XmlNodeKeys::VersionValue);

        XmlSerializingVisitor visitor;

        for (const auto &obj : objects)
        {
            std::visit(visitor, obj.get().GetShape());
            SerializeTransformation(obj.get().GetTransformation(), visitor.objectNode);

            docNode->AddChild(visitor.objectNode);
        }

        doc.SetRoot(docNode);

        return doc;
    }

    void SerializeTransformation(const Transformation &transformation, wxXmlNode *parentNode)
    {
        wxXmlNode *transformationNode = new wxXmlNode(wxXML_ELEMENT_NODE, XmlNodeKeys::TransformationNodeName);

        transformationNode->AddAttribute(XmlNodeKeys::TranslationXAttribute, wxString::FromDouble(transformation.translationX));
        transformationNode->AddAttribute(XmlNodeKeys::TranslationYAttribute, wxString::FromDouble(transformation.translationY));
        transformationNode->AddAttribute(XmlNodeKeys::RotationAttribute, wxString::FromDouble(transformation.rotationAngle));
        transformationNode->AddAttribute(XmlNodeKeys::ScaleXAttribute, wxString::FromDouble(transformation.scaleX));
        transformationNode->AddAttribute(XmlNodeKeys::ScaleYAttribute, wxString::FromDouble(transformation.scaleY));

        parentNode->AddChild(transformationNode);
    }

    std::vector<std::reference_wrapper<CanvasObject>> DeserializeCanvasObjects(const wxXmlDocument &doc)
    {
        std::vector<std::reference_wrapper<CanvasObject>> objects;

        XmlDeserializingShapeFactory factory{};

        for (wxXmlNode *objectNode = doc.GetRoot()->GetChildren(); objectNode != nullptr; objectNode = objectNode->GetNext())
        {
            if (objectNode->GetName() != XmlNodeKeys::ObjectNodeName)
                continue;

            Shape shape = factory.Deserialize(objectNode);
            Transformation transformation = DeserializeTransformation(objectNode);

            wxAffineMatrix2D matrix;
            CanvasObject obj(shape, transformation, matrix);
            objects.push_back(obj);
        }

        return objects;
    }

    Transformation DeserializeTransformation(wxXmlNode *objectNode)
    {
        Transformation t{};

        for (wxXmlNode *node = objectNode->GetChildren(); node != nullptr; node = node->GetNext())
        {
            if (node->GetName() != XmlNodeKeys::TransformationNodeName)
                continue;

            t.translationX = wxAtof(node->GetAttribute(XmlNodeKeys::TranslationXAttribute));
            t.translationY = wxAtof(node->GetAttribute(XmlNodeKeys::TranslationYAttribute));
            t.rotationAngle = wxAtof(node->GetAttribute(XmlNodeKeys::RotationAttribute));
            t.scaleX = wxAtof(node->GetAttribute(XmlNodeKeys::ScaleXAttribute));
            t.scaleY = wxAtof(node->GetAttribute(XmlNodeKeys::ScaleYAttribute));
        }

        return t;
    }

    void CompressXml(const wxXmlDocument &doc, wxOutputStream &outStream)
    {
        wxZipOutputStream zipStream(outStream);

        zipStream.PutNextEntry("paintDocument.xml");
        doc.Save(zipStream);

        zipStream.CloseEntry();

        zipStream.Close();
    }

    void CompressXml(const wxXmlDocument &doc, const wxString &zipFile)
    {
        auto outStream = wxFileOutputStream(zipFile);

        CompressXml(doc, outStream);
        outStream.Close();
    }

    wxXmlDocument DecompressXml(wxInputStream &in)
    {
        wxXmlDocument doc;
        wxZipInputStream zipStream(in);
        std::unique_ptr<wxZipEntry> entry(zipStream.GetNextEntry());

        while (entry)
        {
            wxString entryName = entry->GetName();

            if (entryName == "paintDocument.xml" && zipStream.CanRead())
            {
                doc.Load(zipStream);
                zipStream.CloseEntry();
                break;
            }

            zipStream.CloseEntry();
            entry.reset(zipStream.GetNextEntry());
        }

        return doc;
    }

    wxXmlDocument DecompressXml(const wxString &zipFile)
    {
        wxFileSystem fs;
        std::unique_ptr<wxFSFile> zip(fs.OpenFile(zipFile + "#zip:paintDocument.xml"));

        wxXmlDocument doc;

        if (zip)
        {
            wxInputStream *in = zip->GetStream();

            if (in)
            {
                doc.Load(*in);
            }
        }

        return doc;
    }
};