//
//  strings.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "strings.hpp"

std::wstring_convert<std::codecvt_utf8<wchar_t>> Strings::strConverter;

Strings::Strings(const std::string &language)
  : language(language) {}

void Strings::load() {
  using namespace Resource;
  
  const std::string path = "Strings/" + language + ".xml";
  LOG_DEBUG(UI,
    "Loading strings file for language \"%s\" (actual path \"%s\")",
    language.c_str(), path.c_str());
  
  Resource::ID id(path);
  Handle::Ptr handle = Global::resCache->get(id);
  Descs::XML::Ptr desc = handle->getDesc<Descs::XML>();
  const tinyxml2::XMLElement &root = desc->getRoot();
  
  if (strcmp(root.Name(), "strings")) {
    LOG_ERROR(UI,
      "Tried to load a strings file but it was not a strings file. Its root name was \"%s\"",
      root.Name());
  }
  
  #ifndef NDEBUG
  size_t count = 0;
  
  for (const tinyxml2::XMLElement *i = root.FirstChildElement(); i; i = i->NextSiblingElement(), count++) {
    if (strcmp(i->Name(), "string")) {
      LOG_ERROR(UI,
        "Element in strings file was not a string. Its name was \"%s\"",
        i->Name());
      continue;
    }
    
    const char *id = i->Attribute("id");
    if (id == nullptr) {
      LOG_ERROR(UI,
        "Element in strings file didn't have \"id\" attribute. Its index is %i",
        i->Name(), count);
      continue;
    }
    
    const char *string = i->GetText();
    if (string == nullptr) {
      LOG_ERROR(UI,
        "Element in strings file didn't have text. Its index is %i", count);
      continue;
    }
    
    auto pair = strings.emplace(std::string(id), strConverter.from_bytes(string));
    if (!pair.second) {
      LOG_ERROR(UI,
        "Duplicate string id \"%s", id);
      continue;
    }
  }
  #else
  for (const tinyxml2::XMLElement *i = root.FirstChildElement(); i; i = i->NextSiblingElement()) {
    //assuming the file is valid
    strings.emplace(std::string(i->Attribute("id")), strConverter.from_bytes(i->GetText()));
  }
  #endif
  
}

std::wstring Strings::get(const std::string &id) const {
  auto iter = strings.find(id);
  if (iter == strings.end()) {
    LOG_ERROR(UI,
      "String with ID \"%s\" not found in language \"%s\"", id.c_str(), language.c_str());
    return L"";
  } else {
    return iter->second;
  }
}
