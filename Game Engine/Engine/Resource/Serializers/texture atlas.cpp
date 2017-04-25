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
  struct convert<Res::TextureAtlas::Sprite> {
    static glm::ivec2 textureSize;
    
    static bool decode(const Node &node, Res::TextureAtlas::Sprite &sprite) {
      if (!node.IsSequence() || node.size() != 4) {
        return false;
      }
      
      sprite.left   = node[0].as<decltype(sprite.left  )>() / textureSize.x;
      sprite.top    = node[1].as<decltype(sprite.top   )>() / textureSize.y;
      sprite.right  = node[2].as<decltype(sprite.right )>() / textureSize.x;
      sprite.bottom = node[3].as<decltype(sprite.bottom)>() / textureSize.y;
      
      return 0 <= sprite.left    && sprite.left   <= 1 &&
             0 <= sprite.top     && sprite.top    <= 1 &&
             0 <= sprite.right   && sprite.right  <= 1 &&
             0 <= sprite.bottom  && sprite.bottom <= 1;
    }
  };
  
  glm::ivec2 convert<Res::TextureAtlas::Sprite>::textureSize = {0, 0};
  
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
  
  template <>
  struct convert<Res::TextureAtlas::GlyphMetrics> {
    static bool decode(const Node &node, Res::TextureAtlas::GlyphMetrics &metrics) {
      if (!node.IsMap()) {
        return false;
      }
      
      #define SET_PROPERTY(prop) \
        if (const Node &prop = node[#prop]) { \
          metrics.prop = prop.as<decltype(metrics.prop)>(); \
        } else { \
          return false; \
        }
      
      SET_PROPERTY(bearing);
      SET_PROPERTY(size);
      SET_PROPERTY(advance);
      
      #undef SET_PROPERTY
      
      return true;
    }
  };
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
    YAML::convert<Res::TextureAtlas::Sprite>::textureSize = atlas->textureSize;
    
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
  CHECK_NODE(metrics, charRange["metrics"]);
  atlas->metrics = metrics.as<decltype(atlas->metrics)>();
  CHECK_NODE(glyphs, charRange["glyphs"]);
  atlas->glyphs = glyphs.as<decltype(atlas->glyphs)>();
}

#undef CHECK_NODE

void Res::TextureAtlasSerializer::exportAtlas(const TextureAtlas *atlas, const Ogre::String &string) {
  Ogre::DataStreamPtr stream(new Ogre::FileStreamDataStream(new std::ifstream(string)));
  exportAtlas(atlas, stream);
}

void Res::TextureAtlasSerializer::exportAtlas(const TextureAtlas *, Ogre::DataStreamPtr &) {
  //This isn't needed
}
