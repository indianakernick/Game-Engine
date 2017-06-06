//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

Res::InvalidXMLDocument::InvalidXMLDocument(const std::string &error)
  : InvalidResource("XML", error) {}

std::unique_ptr<tinyxml2::XMLDocument> Res::XMLSerializer::readDocument(const char *data, const size_t size) {
  std::unique_ptr<tinyxml2::XMLDocument> document = std::make_unique<tinyxml2::XMLDocument>();
  
  document->Parse(data, size);
  
  if (document->Error()) {
    const std::string name = document->ErrorName();
    const char *str1 = document->GetErrorStr1();
    str1 = str1 ? str1 : "";
    const char *str2 = document->GetErrorStr2();
    str2 = str2 ? str2 : "";
    throw Res::InvalidXMLDocument(name + ", str1: \"" + str1 + "\", str2: \"" + str2 + "\"");
  }
  
  return document;
}

void Res::XMLSerializer::importDocument(Ogre::DataStreamPtr &stream, XML *doc) {
  assert(stream->isReadable());
  assert(doc);
  
  const std::string string = stream->getAsString();
  doc->document = readDocument(string.data(), string.size());
  doc->root = doc->document->RootElement();
}
