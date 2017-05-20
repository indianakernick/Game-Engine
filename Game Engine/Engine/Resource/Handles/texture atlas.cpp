//
//  texture atlas.cpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture atlas.hpp"

#include "../Serializers/texture atlas.hpp"

const UI::TexCoords Res::TextureAtlas::ZERO_SPRITE = {0.0f, 0.0f, 0.0f, 0.0f};
const Res::TextureAtlas::Glyph Res::TextureAtlas::ZERO_GLYPH = {ZERO_SPRITE, {{0, 0}, {0, 0}, 0}};
const size_t Res::TextureAtlas::ESTIMATE_SPRITE_NAME_LENGTH = 16;

Res::TextureAtlas::Glyph Res::TextureAtlas::FontFace::getGlyph(char c) const {
  if (begin <= c && c < end) {
    return {glyphs[c - begin], metrics[c - begin]};
  } else {
    return ZERO_GLYPH;
  }
}

Res::TextureAtlas::FontMetrics Res::TextureAtlas::FontFace::getFontMetrics() const {
  return fontMetrics;
}

int Res::TextureAtlas::FontFace::getKerning(char left, char right) const {
  if (kerning.size() && begin <= left && left < end && begin <= right && right < end) {
    //                   y        *    width      +        x
    return kerning[(left - begin) * (end - begin) + (right - begin)];
  }
  
  return 0;
}

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
  createParamDictionary("Texture Atlas");
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

bool Res::TextureAtlas::hasWhitepixel() const {
  assert(type == Type::IMAGE);
  
  return whitepixel.left >= 0 && whitepixel.top >= 0;
}

UI::TexCoords Res::TextureAtlas::getWhitepixel() const {
  return whitepixel;
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

const Res::TextureAtlas::FontFace &Res::TextureAtlas::getFontFace(UI::FontSize size) const {
  assert(type == Type::FONT);
  assert(faces.size());
  
  auto iter = faces.find(size);
  if (iter != faces.end()) {
    return iter->second;
  } else {
    //if the exact size isn't available. Find the nearest one
  
    auto greater = faces.upper_bound(size);
    if (greater == faces.end()) {
      return faces.crbegin()->second;
    } else if (greater == faces.begin()) {
      return faces.cbegin()->second;
    }
    
    auto less = std::prev(greater);
    if (size - less->first < greater->first - size) {
      return less->second;
    } else {
      return greater->second;
    }
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
    size_t size = sizeof(faces);
    for (auto f = faces.cbegin(); f != faces.cend(); f++) {
      const FontFace &face = f->second;
      size += sizeof(f->first);
      size += sizeof(f->second);
      size += face.glyphs.size() * sizeof(decltype(face.glyphs)::value_type);
      size += face.metrics.size() * sizeof(decltype(face.metrics)::value_type);
      size += face.kerning.size() * sizeof(decltype(face.kerning)::value_type);
      size += sizeof(face.fontMetrics);
      size += sizeof(face.begin);
      size += sizeof(face.end);
    }
    return size;
  }
}
