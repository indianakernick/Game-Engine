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

template <typename EnumType, size_t SIZE, typename CharType = char>
class StringEnum {
public:
  using String = std::experimental::basic_string_view<CharType>;
  using Strings = std::array<String, SIZE>;
  using CharTraits = std::char_traits<CharType>;

  //I'm not sure if this actually needs a constructor
  //It could just be a class with two static functions

  explicit StringEnum(const String newString) {
    if (newString.data() == nullptr || newString.size() == 0) {
      throw std::runtime_error("Cannot construct StringEnum from empty string");
    }
    string = newString;
    enumValue = getEnumFromString(string);
  }
  explicit StringEnum(const CharType *charPtr) {
    if (charPtr == nullptr || CharTraits::Length(charPtr) == 0) {
      throw std::runtime_error("Cannot construct StringEnum from empty string");
    }
    enumValue = getEnumFromString(string);
  }
  explicit StringEnum(const EnumType enumValue)
    : string(getStringFromEnum(enumValue)), enumValue(enumValue) {}

  String getString() const {
    return string;
  }
  EnumType getEnum() const {
    return enumValue;
  }

  static void setStrings(const Strings &newStrings) {
    if (locked) {
      throw std::logic_error("Strings can only be set once");
    } else {
      strings = newStrings;
      locked = true;
    }
  }

private:
  using IntType = uint_fit_t<EnumType>;
  
  static_assert(std::is_integral<IntType>::value);
  static_assert(std::numeric_limits<IntType>::max() >= SIZE);

public:
  static EnumType getEnumFromString(const String string) {
    IntType value = 0;
    while (value < SIZE && strings[value] != string) {
      value++;
    }
    if (value == SIZE) {
      throw std::range_error("Invalid enum string \""s + string.data() + "\"");
    }
    return static_cast<EnumType>(value);
  }

  static String getStringFromEnum(const EnumType enumValue) {
    const IntType intValue = static_cast<IntType>(enumValue);
    if (intValue < 0 || intValue >= SIZE) {
      throw std::range_error("Invalid enum value");
    }
    return strings[intValue];
  }

private:
  static bool locked;
  static Strings strings;
  
  String string;
  EnumType enumValue;
};

template <typename EnumType, size_t SIZE, typename CharType>
bool StringEnum<EnumType, SIZE, CharType>::locked = false;

template <typename EnumType, size_t SIZE, typename CharType>
typename StringEnum<EnumType, SIZE, CharType>::Strings StringEnum<EnumType, SIZE, CharType>::strings;

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
  const StringView docName = "screen";

  //elements
  const StringView buttonName = "button";
  const StringView imageName = "image";
  const StringView checkboxName = "checkbox";
  const StringView radioName = "radio";
  const StringView captionName = "caption";
  const StringView paragraphName = "paragraph";

  using BoolStringEnum = StringEnum<bool, 2>;
  using OriginStringEnum = StringEnum<UI::Origin, 9>;
  using SpaceStringEnum = StringEnum<UI::Space, 2>;
  using AxisStringEnum = StringEnum<UI::Axis, 5>;
  using AlignStringEnum = StringEnum<UI::Paragraph::Align, 3>;
}

const int n = []{
  BoolStringEnum::setStrings({{"false", "true"}});
  OriginStringEnum::setStrings({{"top-left", "top", "top-right", "right", "bottom-right", "bottom", "bottom-left", "left", "center"}});
  SpaceStringEnum::setStrings({{"rel", "abs"}});
  AxisStringEnum::setStrings({{"both", "hori", "vert", "max", "min"}});
  AlignStringEnum::setStrings({{"left", "center", "right"}});

  return 0;
}();

namespace {
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
      return BoolStringEnum::getEnumFromString(checkedStr);
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

  //caption and paragraph have the same API but are different types
  //does caption even need to exist?
  //@TODO delete caption
  UI::Caption::Ptr readCaption(const tinyxml2::XMLElement *xmlElement, const char *id) {
    UI::Caption::Ptr caption = std::make_shared<UI::Caption>(id);
    if (const tinyxml2::XMLElement *styleElement = xmlElement->FirstChildElement("style")) {
      if (const tinyxml2::XMLElement *fontElement = xmlElement->FirstChildElement("font")) {
        caption->setFont(emptyIfNull(fontElement->GetText()));
      }
      if (const tinyxml2::XMLElement *fontSizeElement = xmlElement->FirstChildElement("font_size")) {
        UI::FontSize fontSize = UI::SMALLEST_FONT_SIZE;
        fontSizeElement->QueryUnsignedText(&fontSize);
        caption->setFontSize(fontSize);
      }
      if (const tinyxml2::XMLElement *textElement = xmlElement->FirstChildElement("text")) {
        caption->setText(emptyIfNull(textElement->GetText()));
      }
    }
    return caption;
  }

  UI::Paragraph::Ptr readParagraph(const tinyxml2::XMLElement *xmlElement, const char *id) {
    UI::Paragraph::Ptr paragraph = std::make_shared<UI::Paragraph>(id);
    if (const tinyxml2::XMLElement *styleElement = xmlElement->FirstChildElement("style")) {
      if (const tinyxml2::XMLElement *fontElement = xmlElement->FirstChildElement("font")) {
        paragraph->setFont(emptyIfNull(fontElement->GetText()));
      }
      if (const tinyxml2::XMLElement *fontSizeElement = xmlElement->FirstChildElement("font_size")) {
        UI::FontSize fontSize = UI::SMALLEST_FONT_SIZE;
        fontSizeElement->QueryUnsignedText(&fontSize);
        paragraph->setFontSize(fontSize);
      }
      if (const tinyxml2::XMLElement *textElement = xmlElement->FirstChildElement("text")) {
        paragraph->setText(emptyIfNull(textElement->GetText()));
      }
      if (const tinyxml2::XMLElement *alignElement = xmlElement->FirstChildElement("align")) {
        paragraph->setAlign(AlignStringEnum::getEnumFromString(alignElement->GetText()));
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
      element->setPassthrough(BoolStringEnum::getEnumFromString(passthrough));
    }
    
    UI::AABB bounds;
    if (const tinyxml2::XMLElement *posElement = xmlBounds->FirstChildElement("pos")) {
      glm::vec2 pos = {0.0f, 0.0f};
      posElement->QueryFloatAttribute("x", &pos.x);
      posElement->QueryFloatAttribute("y", &pos.y);
      bounds.setPos(pos);
      
      if (const char *spaceStr = posElement->Attribute("space")) {
        bounds.setPosSpace(SpaceStringEnum::getEnumFromString(spaceStr));
      }
      if (const char *thisOriginStr = posElement->Attribute("thisOrigin")) {
        bounds.setThisOrigin(OriginStringEnum::getEnumFromString(thisOriginStr));
      }
      if (const char *parentOriginStr = posElement->Attribute("parentOrigin")) {
        bounds.setParentOrigin(OriginStringEnum::getEnumFromString(parentOriginStr));
      }
    }
    if (const tinyxml2::XMLElement *sizeElement = xmlBounds->FirstChildElement("size")) {
      glm::vec2 size = {1.0f, 1.0f};
      sizeElement->QueryFloatAttribute("width", &size.x);
      sizeElement->QueryFloatAttribute("height", &size.y);
      bounds.setSize(size);

      if (const char *spaceStr = sizeElement->Attribute("space")) {
        bounds.setSizeSpace(SpaceStringEnum::getEnumFromString(spaceStr));
      }
      if (const char *axisStr = sizeElement->Attribute("axis")) {
        bounds.setSizeAxis(AxisStringEnum::getEnumFromString(axisStr));
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
    } else if (xmlElement->Name() == captionName) {
      element = readCaption(xmlElement, id);
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
