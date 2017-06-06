//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

#include "../Serializers/xml.hpp"

Res::XML::XML(
  Ogre::ResourceManager *creator,
  const Ogre::String &name,
  Ogre::ResourceHandle handle,
  const Ogre::String &group,
  bool isManual,
  Ogre::ManualResourceLoader *loader
) : Ogre::Resource(creator, name, handle, group, isManual, loader) {
  createParamDictionary("XML");
}

Res::XML::~XML() {
  unload();
}

const tinyxml2::XMLDocument *Res::XML::getDocument() const {
  return document.get();
}

const tinyxml2::XMLElement *Res::XML::getRoot() const {
  return root;
}

void Res::XML::loadImpl() {
  XMLSerializer serializer;
  Ogre::DataStreamPtr stream =
    Ogre::ResourceGroupManager::getSingleton().openResource(mName, mGroup, true, this);
  serializer.importDocument(stream, this);
}

void Res::XML::unloadImpl() {

}

size_t Res::XML::calculateSize() const {
  //I could traverse the tree but I don't see the point
  //10KB
  return 10240;
}
