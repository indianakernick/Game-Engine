//
//  texture atlas.cpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture atlas.hpp"

namespace YAML {
  template <>
  struct convert<UI::TexCoords> {
    static glm::ivec2 textureSize;
    
    static bool decode(const Node &node, UI::TexCoords &sprite) {
      if (!node.IsSequence() || node.size() != 4) {
        return false;
      }
      
      const UI::TexCoordsPx spritePx = {
        node[0].as<int>(),//left
        node[1].as<int>(),//top
        node[2].as<int>(),//right
        node[3].as<int>() //bottom
      };
      sprite = UI::fromPixels(spritePx, textureSize);
      
      return UI::TexCoords::NORM_0_1.encloses(sprite);
    }
  };
  
  UI::PointPx convert<UI::TexCoords>::textureSize = {0, 0};
  
  template <typename T>
  struct convert<glm::tvec2<T>> {
    static bool decode(const Node &node, glm::tvec2<T> &vector) {
      if (!node.IsSequence() || node.size() != 2) {
        return false;
      }
      
      vector[0] = node[0].as<T>();
      vector[1] = node[1].as<T>();
      
      return true;
    }
  };
  
  #define SET_PROPERTY(prop) \
    if (const Node &prop = node[#prop]) { \
      obj.prop = prop.as<decltype(obj.prop)>(); \
    } else { \
      return false; \
    }
  
  #define SET_NAMED_PROPERTY(prop, propName) \
    if (const Node &prop = node[#propName]) { \
      obj.prop = prop.as<decltype(obj.prop)>(); \
    } else { \
      return false; \
    }
  
  template <>
  struct convert<Res::TextureAtlas::GlyphMetrics> {
    static bool decode(const Node &node, Res::TextureAtlas::GlyphMetrics &obj) {
      if (!node.IsMap()) {
        return false;
      }
      
      SET_PROPERTY(bearing);
      SET_PROPERTY(size);
      SET_PROPERTY(advance);
      
      return true;
    }
  };
  
  template <>
  struct convert<Res::TextureAtlas::FontMetrics> {
    static bool decode(const Node &node, Res::TextureAtlas::FontMetrics &obj) {
      if (!node.IsMap()) {
        return false;
      }
      
      SET_NAMED_PROPERTY(lineHeight, line height);
      SET_NAMED_PROPERTY(minY, min y);
      SET_NAMED_PROPERTY(maxY, max y);
      
      return true;
    }
  };
  
  #undef SET_PROPERTY
  #undef SET_NAMED_PROPERTY
}

#define CHECK_NODE(varName, node) \
  const YAML::Node &varName = node; \
  if (!varName) { \
    LOG_ERROR(RESOURCES, "Part of the texture atlas is missing"); \
    return; \
  }

void Res::TextureAtlasSerializer::importAtlas(Ogre::DataStreamPtr &stream, TextureAtlas *atlas) {
  assert(stream->isReadable());
  assert(atlas);
  
  try {
    const YAML::Node doc = YAML::Load(stream->getAsString());
    
    CHECK_NODE(head, doc["head"]);
    CHECK_NODE(texSize, head["texture size"]);
    atlas->textureSize = texSize.as<decltype(atlas->textureSize)>();
    if (atlas->textureSize.x <= 0 || atlas->textureSize.y <= 0) {
      LOG_ERROR(RESOURCES, "Atlas has negative size");
      return;
    }
    YAML::convert<UI::TexCoords>::textureSize = atlas->textureSize;
    
    CHECK_NODE(body, doc["body"]);
    CHECK_NODE(type, head["type"]);
    const std::string strType = type.as<std::string>();
    if (strType == "image") {
      atlas->type = TextureAtlas::Type::IMAGE;
      importImageAtlas(body, atlas);
    } else if (strType == "font") {
      atlas->type = TextureAtlas::Type::FONT;
      importFontAtlas(body, atlas);
    } else {
      LOG_ERROR(RESOURCES, "head.type is invalid");
    }
    
  } catch (YAML::Exception &e) {
    LOG_ERROR(RESOURCES, "%s", e.what());
  }
}

void Res::TextureAtlasSerializer::importImageAtlas(const YAML::Node &body, Res::TextureAtlas *atlas) {
  atlas->sprites = body.as<decltype(atlas->sprites)>();
}

void Res::TextureAtlasSerializer::importFontAtlas(const YAML::Node &body, Res::TextureAtlas *atlas) {
  CHECK_NODE(charRange, body[0]);
  CHECK_NODE(range, charRange["range"]);
  atlas->beginChar = range[0].as<int>();
  atlas->endChar = range[1].as<int>();
  CHECK_NODE(fontMetrics, charRange["font metrics"]);
  atlas->fontMetrics = fontMetrics.as<decltype(atlas->fontMetrics)>();
  CHECK_NODE(metrics, charRange["glyph metrics"]);
  atlas->metrics = metrics.as<decltype(atlas->metrics)>();
  CHECK_NODE(glyphs, charRange["glyphs"]);
  atlas->glyphs = glyphs.as<decltype(atlas->glyphs)>();
  CHECK_NODE(hasKerning, charRange["has kerning"]);
  if (hasKerning.as<bool>()) {
    CHECK_NODE(kerning, charRange["kerning"]);
    atlas->kerning = kerning.as<decltype(atlas->kerning)>();
  }
}

#undef CHECK_NODE

void Res::TextureAtlasSerializer::exportAtlas(const TextureAtlas *atlas, const Ogre::String &string) {
  Ogre::DataStreamPtr stream(new Ogre::FileStreamDataStream(new std::ifstream(string)));
  exportAtlas(atlas, stream);
}

void Res::TextureAtlasSerializer::exportAtlas(const TextureAtlas *, Ogre::DataStreamPtr &) {
  //This isn't needed
}
