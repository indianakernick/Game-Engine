//
//  ui screen.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ui screen.hpp"

using namespace std::literals;

Res::InvalidUIScreen::InvalidUIScreen(const std::string &error)
  : InvalidResource("UI Screen", error) {}

namespace {
  std::unique_ptr<tinyxml2::XMLDocument> loadDocument(const char *data, size_t size) {
    std::unique_ptr<tinyxml2::XMLDocument> document = std::make_unique<tinyxml2::XMLDocument>();
    
    document->Parse(data, size);
    
    if (document->Error()) {
      const std::string name = document->ErrorName();
      const char *str1 = document->GetErrorStr1();
      str1 = str1 ? str1 : "";
      const char *str2 = document->GetErrorStr2();
      str2 = str2 ? str2 : "";
      throw Res::InvalidUIScreen(name + ", str1: \"" + str1 + "\", str2: \"" + str2 + "\"");
    }
    
    return document;
  }
  
  using StringView = std::experimental::string_view;

  const StringView boolStrings[] = {"no", "yes"};
  using BoolStringEnum = StringEnum<bool, 2, boolStrings>;
  const StringView originStrings[] = {"top-left", "top", "top-right", "right", "bottom-right", "bottom", "bottom-left", "left", "center"};
  using OriginStringEnum = StringEnum<UI::Origin, 9, originStrings>;
  const StringView spaceStrings[] = {"rel", "abs"};
  using SpaceStringEnum = StringEnum<UI::Space, 2, spaceStrings>;
  const StringView axisStrings[] = {"both", "hori", "vert", "max", "min"};
  using AxisStringEnum = StringEnum<UI::Axis, 5, axisStrings>;
  const StringView alignStrings[] = {"left", "center", "right"};
  using AlignStringEnum = StringEnum<UI::Paragraph::Align, 3, alignStrings>;
  
  const char *emptyIfNull(const char *str) {
    return str == nullptr ? "" : str;
  }

  UI::Button::Ptr readButton(const tinyxml2::XMLElement *, const char *id) {
    return std::make_shared<UI::Button>(id);
  }

  UI::Image::Ptr readImage(const tinyxml2::XMLElement *, const char *id) {
    return std::make_shared<UI::Image>(id);
  }

  bool readChecked(const tinyxml2::XMLElement *xmlElement) {
    if (const char *checkedStr = xmlElement->Attribute("checked")) {
      return BoolStringEnum::strToEnum(checkedStr);
    } else {
      return false;
    }
  }  

  UI::Checkbox::Ptr readCheckbox(const tinyxml2::XMLElement *xmlElement, const char *id) {
    return std::make_shared<UI::Checkbox>(id, readChecked(xmlElement));
  }

  UI::Radio::Ptr readRadio(const tinyxml2::XMLElement *xmlElement, const char *id) {
    return std::make_shared<UI::Radio>(id, readChecked(xmlElement));
  }

  UI::Paragraph::Ptr readParagraph(const tinyxml2::XMLElement *xmlElement, const char *id) {
    UI::Paragraph::Ptr paragraph = std::make_shared<UI::Paragraph>(id);
    if (const tinyxml2::XMLElement *styleElement = xmlElement->FirstChildElement("style")) {
      if (const tinyxml2::XMLElement *fontElement = styleElement->FirstChildElement("font")) {
        paragraph->setFont(emptyIfNull(fontElement->GetText()));
      }
      if (const tinyxml2::XMLElement *fontSizeElement = styleElement->FirstChildElement("font_size")) {
        UI::FontSize fontSize = UI::SMALLEST_FONT_SIZE;
        fontSizeElement->QueryUnsignedText(&fontSize);
        paragraph->setFontSize(fontSize);
      }
      if (const tinyxml2::XMLElement *textElement = styleElement->FirstChildElement("text")) {
        paragraph->setText(emptyIfNull(textElement->GetText()));
      }
      if (const tinyxml2::XMLElement *alignElement = styleElement->FirstChildElement("align")) {
        paragraph->setAlign(AlignStringEnum::strToEnum(alignElement->GetText()));
      }
      if (const tinyxml2::XMLElement *wrapElement = styleElement->FirstChildElement("wrap")) {
        paragraph->setWrap(BoolStringEnum::strToEnum(wrapElement->GetText()));
      }
    }
    return paragraph;
  }

  void readBounds(UI::Element::Ptr element, const tinyxml2::XMLElement *xmlBounds) {
    if (xmlBounds == nullptr) {
      return;
    }
    
    UI::Height height = 1;
    xmlBounds->QueryIntAttribute("height", &height);
    element->setHeight(height);

    if (const char *passthrough = xmlBounds->Attribute("passthrough")) {
      element->setPassthrough(BoolStringEnum::strToEnum(passthrough));
    }
    
    UI::AABB bounds;
    if (const tinyxml2::XMLElement *posElement = xmlBounds->FirstChildElement("pos")) {
      glm::vec2 pos = {0.0f, 0.0f};
      posElement->QueryFloatAttribute("x", &pos.x);
      posElement->QueryFloatAttribute("y", &pos.y);
      bounds.setPos(pos);
      
      if (const char *spaceStr = posElement->Attribute("space")) {
        bounds.setPosSpace(SpaceStringEnum::strToEnum(spaceStr));
      }
      if (const char *thisOriginStr = posElement->Attribute("thisOrigin")) {
        bounds.setThisOrigin(OriginStringEnum::strToEnum(thisOriginStr));
      }
      if (const char *parentOriginStr = posElement->Attribute("parentOrigin")) {
        bounds.setParentOrigin(OriginStringEnum::strToEnum(parentOriginStr));
      }
    }
    if (const tinyxml2::XMLElement *sizeElement = xmlBounds->FirstChildElement("size")) {
      glm::vec2 size = {1.0f, 1.0f};
      sizeElement->QueryFloatAttribute("width", &size.x);
      sizeElement->QueryFloatAttribute("height", &size.y);
      bounds.setSize(size);

      if (const char *spaceStr = sizeElement->Attribute("space")) {
        bounds.setSizeSpace(SpaceStringEnum::strToEnum(spaceStr));
      }
      if (const char *axisStr = sizeElement->Attribute("axis")) {
        bounds.setSizeAxis(AxisStringEnum::strToEnum(axisStr));
      }
    }
    element->setBounds(bounds);
  }

  void readHitregion(UI::Element::Ptr element, const tinyxml2::XMLElement *xmlHitregion) {
    if (xmlHitregion == nullptr) {
      return;
    }
    UI::Polygon polygon;
    const char *str = emptyIfNull(xmlHitregion->GetText());
    char *end = nullptr;
    while (true) {
      //@TODO refactor this
      const float x = std::strtof(str, &end);
      if (end == str || *end == 0) {
        break;
      }
      str = end;
      const float y = std::strtof(str, &end);
      if (end == str || *end == 0) {
        break;
      }
      str = end;
      polygon.push_back({x, y});
    }
    element->setHitRegion(polygon);
  }

  void readStyle(UI::Element::Ptr element, const tinyxml2::XMLElement *xmlStyle) {
    if (xmlStyle == nullptr) {
      return;
    } 
    UI::Color color = {1.0f, 1.0f, 1.0f, 1.0f};
    if (const tinyxml2::XMLElement *colorElement = xmlStyle->FirstChildElement("color")) {
      colorElement->QueryFloatAttribute("r", &color.r);
      colorElement->QueryFloatAttribute("g", &color.g);
      colorElement->QueryFloatAttribute("b", &color.b);
      colorElement->QueryFloatAttribute("a", &color.a);
    }
    element->setColor(color);
    
    if (const tinyxml2::XMLElement *textureElement = xmlStyle->FirstChildElement("texture")) {
      element->setTexture(emptyIfNull(textureElement->GetText()));
    }
  }
 
   UI::Element::Ptr readElement(const tinyxml2::XMLElement *);
 
  void readChildren(UI::Element::Ptr element, const tinyxml2::XMLElement *xmlChildren) {
    if (xmlChildren == nullptr) {
      return;
    }
    for (const tinyxml2::XMLElement *child = xmlChildren->FirstChildElement(); child; child = child->NextSiblingElement()) {
      element->addChild(readElement(child));
    }
  }
  
  //comparing against string views so that i can use == instead of strcmp
  const StringView docName = "screen";
  const StringView buttonName = "button";
  const StringView imageName = "image";
  const StringView checkboxName = "checkbox";
  const StringView radioName = "radio";
  const StringView paragraphName = "paragraph";

  UI::Element::Ptr readElement(const tinyxml2::XMLElement *xmlElement) {
    UI::Element::Ptr element = nullptr;
    const char *id = xmlElement->Attribute("id");
    if (id == nullptr || strlen(id) == 0) {
      throw Res::InvalidUIScreen("All elements must have an ID");
    }

           if (xmlElement->Name() == buttonName) {
      element = readButton(xmlElement, id);
    } else if (xmlElement->Name() == imageName) {
      element = readImage(xmlElement, id);
    } else if (xmlElement->Name() == checkboxName) {
      element = readCheckbox(xmlElement, id);
    } else if (xmlElement->Name() == radioName) {
      element = readRadio(xmlElement, id);
    } else if (xmlElement->Name() == paragraphName) {
      element = readParagraph(xmlElement, id);
    }

    if (element == nullptr) {
      throw Res::InvalidUIScreen("Invalid element type \""s + xmlElement->Name() + "\"");
    }
    
    readBounds(element, xmlElement->FirstChildElement("bounds"));
    readHitregion(element,xmlElement->FirstChildElement("hitregion"));
    readStyle(element, xmlElement->FirstChildElement("style"));
    readChildren(element, xmlElement->FirstChildElement("children"));

    return element;
  }
}

void Res::UIScreenSerializer::importScreen(Ogre::DataStreamPtr &stream, UIScreen *screen) {
  assert(stream->isReadable());
  assert(screen);
  
  const std::string string = stream->getAsString();
  std::unique_ptr<tinyxml2::XMLDocument> document = loadDocument(string.data(), string.size());
  const tinyxml2::XMLElement *root = document->RootElement();
  
  if (root->Name() != docName) {
    throw InvalidUIScreen("This is not a UI screen document");
  }
  const tinyxml2::XMLElement *rootElement = root->FirstChildElement();
  if (rootElement == nullptr) {
    throw InvalidUIScreen("Screen doesn't have a root element");
  }
  try {
    screen->root = readElement(rootElement);
  } catch (std::exception &e) {
    throw InvalidUIScreen(e.what());
  }
}
