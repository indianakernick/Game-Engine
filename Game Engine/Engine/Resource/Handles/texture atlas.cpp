//
//  texture atlas.cpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture atlas.hpp"
#include "../serializers/texture atlas.hpp"

const size_t Res::TextureAtlas::ESTIMATE_SPRITE_NAME_LENGTH = 16;

Res::TextureAtlas::TextureAtlas(
  Ogre::ResourceManager *creator,
  const Ogre::String &name,
  Ogre::ResourceHandle handle,
  const Ogre::String &group,
  bool isManual,
  Ogre::ManualResourceLoader *loader
) : Ogre::Resource(creator, name, handle, group, isManual, loader) {
  createParamDictionary("TextureAtlas");
}

Res::TextureAtlas::~TextureAtlas() {
  unload();
}

Res::TextureAtlas::Sprite Res::TextureAtlas::getSprite(const std::string &name) const {
  auto iter = sprites.find(name);
  if (iter == sprites.end()) {
    LOG_ERROR(UI,
      "Tried to get sprite \"%s\" but it wasn't in the atlas",
      name.c_str());
    return {0.0f, 0.0f, 0.0f, 0.0f};
  } else {
    return iter->second;
  }
}

void Res::TextureAtlas::loadImpl() {
  TextureAtlasSerializer serializer;
  Ogre::DataStreamPtr stream =
    Ogre::ResourceGroupManager::getSingleton().openResource(mName, mGroup, true, this);
  serializer.importAtlas(stream, this);
}

void Res::TextureAtlas::unloadImpl() {
  
}

size_t Res::TextureAtlas::calculateSize() const {
  return sprites.size() * (
    sizeof(Sprite) +
    ESTIMATE_SPRITE_NAME_LENGTH * sizeof(
      decltype(sprites)::key_type::value_type
    )
  );
}
