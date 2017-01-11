//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

const std::string &Resource::Loaders::XML::getName() {
  static const std::string NAME = "XML";
  return NAME;
}

bool Resource::Loaders::XML::canLoad(const std::string &fileExt) {
  return fileExt == "xml";
}

Resource::Handle::Ptr Resource::Loaders::XML::load(const ID &id) {
  std::shared_ptr<tinyxml2::XMLDocument> document = std::make_shared<tinyxml2::XMLDocument>();
  std::pair<Memory::Buffer,bool> filePair = readFile(id);
  if (!filePair.second) {
    LOG_ERROR(RESOURCES, "Failed to open file \"%s\"", id.getPathC());
    return nullptr;
  }
  
  document->Parse(reinterpret_cast<const char *>(filePair.first.begin()),
                 filePair.first.size());
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
    Handle::Ptr handle = std::make_shared<Handles::XML>(document);
    //i have no idea how much memory a document uses and i have no idea
    //how rough this guess is
    handle->setSize(filePair.first.size() * 2);
    return handle;
  }
}
