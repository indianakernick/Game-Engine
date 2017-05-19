//
//  ui screen.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ui screen.hpp"

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
  
  const std::string docName = "screen";
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
  
}
