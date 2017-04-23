//
//  texture atlas.cpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture atlas.hpp"

template <>
Res::TextureAtlasManager *Ogre::Singleton<Res::TextureAtlasManager>::msSingleton = nullptr;

Res::TextureAtlasManager::TextureAtlasManager() {
  mResourceType = "TextureAtlas";
  mLoadOrder = 1.0f;
  
  Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}

Res::TextureAtlasManager::~TextureAtlasManager() {
  Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

Ogre::Resource *Res::TextureAtlasManager::createImpl(
  const Ogre::String &name,
  Ogre::ResourceHandle handle,
  const Ogre::String &group,
  bool isManual,
  Ogre::ManualResourceLoader *loader,
  const Ogre::NameValuePairList *
) {
  return new TextureAtlas(this, name, handle, group, isManual, loader);
}
