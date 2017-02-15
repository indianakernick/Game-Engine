//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

using namespace Res;

const std::string &XMLLoader::getName() const {
  static const std::string NAME = "XML";
  return NAME;
}

bool XMLLoader::canLoad(const std::string &ext) const {
  return ext == "xml";
}

Res::Handle::Ptr XMLLoader::load(const ID &id) const {
  std::shared_ptr<tinyxml2::XMLDocument> document = std::make_shared<tinyxml2::XMLDocument>();
  Memory::Buffer file = readFile(id);
  
  document->Parse(reinterpret_cast<const char *>(file.begin()), file.size());
  if (document->Error()) {
    const char *name = document->ErrorName();
    const char *str1 = document->GetErrorStr1();
    str1 = str1 ? str1 : "";
    const char *str2 = document->GetErrorStr2();
    str2 = str2 ? str2 : "";
    LOG_ERROR(RESOURCES,
      "Failed to load file \"%s\". TinyXML2 - %s, str1: \"%s\", str2: \"%s\"",
      id.getPathC(), name, str1, str2);
    return nullptr;
  } else {
    Handle::Ptr handle = std::make_shared<XML>(document);
    //i have no idea how much memory a document uses and i have no idea
    //how rough this guess is
    handle->setSize(file.size() * 2);
    return handle;
  }
}
