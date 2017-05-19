//
//  ui screen.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ui screen.hpp"

template <>
Res::UIScreenManager *Ogre::Singleton<Res::UIScreenManager>::msSingleton = nullptr;

Res::UIScreenManager::UIScreenManager() {
  mResourceType = "UI Screen";
  mLoadOrder = 1.0f;
  
  Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}

Res::UIScreenManager::~UIScreenManager() {
  Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

Ogre::Resource *Res::UIScreenManager::createImpl(
  const Ogre::String &name,
  Ogre::ResourceHandle handle,
  const Ogre::String &group,
  bool isManual,
  Ogre::ManualResourceLoader *loader,
  const Ogre::NameValuePairList *
) {
  return new UIScreen(this, name, handle, group, isManual, loader);
}
