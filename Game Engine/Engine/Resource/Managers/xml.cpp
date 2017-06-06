//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

template <>
Res::XMLManager *Ogre::Singleton<Res::XMLManager>::msSingleton = nullptr;

Res::XMLManager::XMLManager() {
  mResourceType = "XML";
  mLoadOrder = 1.0f;
  
  Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}

Res::XMLManager::~XMLManager() {
  Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

Ogre::Resource *Res::XMLManager::createImpl(
  const Ogre::String &name,
  Ogre::ResourceHandle handle,
  const Ogre::String &group,
  bool isManual,
  Ogre::ManualResourceLoader *loader,
  const Ogre::NameValuePairList *
) {
  return new XML(this, name, handle, group, isManual, loader);
}
