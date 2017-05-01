//
//  texture atlas.cpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture atlas.hpp"
#include "../serializers/texture atlas.hpp"

const UI::TexCoords Res::TextureAtlas::ZERO_SPRITE = {0.0f, 0.0f, 0.0f, 0.0f};
const Res::TextureAtlas::Glyph Res::TextureAtlas::ZERO_GLYPH = {ZERO_SPRITE, {{0, 0}, {0, 0}, 0}};
const size_t Res::TextureAtlas::ESTIMATE_SPRITE_NAME_LENGTH = 16;

bool Res::TextureAtlas::isZero(const Glyph &glyph) {
  return glyph.glyph == ZERO_GLYPH.glyph                     &&
         glyph.metrics.bearing == ZERO_GLYPH.metrics.bearing &&
         glyph.metrics.size    == ZERO_GLYPH.metrics.size    &&
         glyph.metrics.advance == ZERO_GLYPH.metrics.advance;
}

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

UI::PointPx Res::TextureAtlas::getTextureSize() const {
  return textureSize;
}

UI::TexCoords Res::TextureAtlas::getSprite(const std::string &name) const {
  assert(type == Type::IMAGE);
  
  auto iter = sprites.find(name);
  if (iter == sprites.end()) {
    return ZERO_SPRITE;
  } else {
    return iter->second;
  }
}

Res::TextureAtlas::Glyph Res::TextureAtlas::getGlyph(wchar_t c) const {
  assert(type == Type::FONT);
  if (beginChar <= c && c < endChar) {
    return {glyphs[c - beginChar], metrics[c - beginChar]};
  } else {
    return ZERO_GLYPH;
  }
}

Res::TextureAtlas::FontMetrics Res::TextureAtlas::getFontMetrics() const {
  assert(type == Type::FONT);

  return fontMetrics;
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
      sizeof(UI::TexCoords) +
      ESTIMATE_SPRITE_NAME_LENGTH * sizeof(
        decltype(sprites)::key_type::value_type
      )
    );
  } else {//type == Type::FONT
    return sizeof(beginChar) +
           sizeof(endChar) +
           sizeof(fontMetrics) +
           glyphs.size() * sizeof(UI::TexCoords) +
           metrics.size() * sizeof(GlyphMetrics) +
           kerning.size() * sizeof(decltype(kerning)::value_type);
  }
}
