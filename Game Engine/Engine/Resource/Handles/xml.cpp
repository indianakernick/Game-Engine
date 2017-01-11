//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

Resource::Handles::XML::XML(std::shared_ptr<tinyxml2::XMLDocument> document)
  : document(document) {}

const tinyxml2::XMLDocument &Resource::Handles::XML::getDoc() const {
  return *document;
}

const tinyxml2::XMLElement &Resource::Handles::XML::getRoot() const {
  return *document->RootElement();
}
