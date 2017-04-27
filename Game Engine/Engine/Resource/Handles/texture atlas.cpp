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

Res::TextureAtlas::Type Res::TextureAtlas::getType() const {
  return type;
}

Res::TextureAtlas::Sprite Res::TextureAtlas::getSprite(const std::string &name) const {
  assert(type == Type::IMAGE);
  
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

Res::TextureAtlas::Glyph Res::TextureAtlas::getGlyph(wchar_t c) const {
  assert(type == Type::FONT);
  assert(beginChar <= c && c < endChar);
  
  return {glyphs[c - beginChar], metrics[c - beginChar]};
}

int Res::TextureAtlas::getLineHeight() const {
  assert(type == Type::FONT);

  return lineHeight;
}

int Res::TextureAtlas::getKerning(wchar_t left, wchar_t right) const {
  assert(type == Type::FONT);
  
  if (kerning.size() && beginChar <= left && left < endChar && beginChar <= right && right < endChar) {
    //                   y            *        width          +        x
    return kerning[(left - beginChar) * (endChar - beginChar) + (right - beginChar)];
  } else {
    return 0;
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
  if (type == Type::IMAGE) {
    return sprites.size() * (
      sizeof(Sprite) +
      ESTIMATE_SPRITE_NAME_LENGTH * sizeof(
        decltype(sprites)::key_type::value_type
      )
    );
  } else {//type == Type::FONT
    return sizeof(beginChar) +
           sizeof(endChar) +
           sizeof(lineHeight) +
           glyphs.size() * sizeof(Sprite) +
           metrics.size() * sizeof(GlyphMetrics) +
           kerning.size() * sizeof(decltype(kerning)::value_type);
  }
}
