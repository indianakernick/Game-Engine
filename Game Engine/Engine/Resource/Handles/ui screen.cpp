//
//  ui screen.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ui screen.hpp"

#include "../Serializers/ui screen.hpp"

Res::UIScreen::UIScreen(
  Ogre::ResourceManager *creator,
  const Ogre::String &name,
  Ogre::ResourceHandle handle,
  const Ogre::String &group,
  bool isManual,
  Ogre::ManualResourceLoader *loader
) : Ogre::Resource(creator, name, handle, group, isManual, loader) {
  createParamDictionary("UI Screen");
}

Res::UIScreen::~UIScreen() {
  unload();
}

UI::Element::Ptr Res::UIScreen::getRoot() const {
  return root;
}

const std::string &Res::UIScreen::getMaterialName() const {
  return materialName;
}

const std::string &Res::UIScreen::getAtlasName() const {
  return atlasName;
}

void Res::UIScreen::loadImpl() {
  UIScreenSerializer serializer;
  Ogre::DataStreamPtr stream =
    Ogre::ResourceGroupManager::getSingleton().openResource(mName, mGroup, true, this);
  serializer.importScreen(stream, this);
}

void Res::UIScreen::unloadImpl() {

}

size_t Res::UIScreen::calculateSize() const {
  //should I traverse the tree?
  //does it really matter?
  return sizeof(root);
}
