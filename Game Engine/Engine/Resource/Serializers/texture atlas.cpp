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
    static Res::TextureAtlas::Size textureSize;
  
    static Node encode(const Res::TextureAtlas::Sprite &sprite) {
      Node out;
      
      out.push_back(sprite.left   * textureSize.width);
      out.push_back(sprite.top    * textureSize.height);
      out.push_back(sprite.right  * textureSize.width);
      out.push_back(sprite.bottom * textureSize.height);
      
      return out;
    }
    
    static bool decode(const Node &node, Res::TextureAtlas::Sprite &sprite) {
      if (!node.IsSequence() || node.size() != 4) {
        return false;
      }
      
      sprite.left   = node[0].as<decltype(sprite.left  )>() / textureSize.width;
      sprite.top    = node[1].as<decltype(sprite.top   )>() / textureSize.height;
      sprite.right  = node[2].as<decltype(sprite.right )>() / textureSize.width;
      sprite.bottom = node[3].as<decltype(sprite.bottom)>() / textureSize.height;
      
      return 0 <= sprite.left    && sprite.left   <= 1 &&
             0 <= sprite.top     && sprite.top    <= 1 &&
             0 <= sprite.right   && sprite.right  <= 1 &&
             0 <= sprite.bottom  && sprite.bottom <= 1;
    }
  };
  
  Res::TextureAtlas::Size convert<Res::TextureAtlas::Sprite>::textureSize = {0, 0};
  
  template <>
  struct convert<Res::TextureAtlas::Size> {
    static Node encode(const Res::TextureAtlas::Size &size) {
      Node out;
      
      out.push_back(size.width);
      out.push_back(size.height);
      
      return out;
    }
    
    static bool decode(const Node &node, Res::TextureAtlas::Size &size) {
      if (!node.IsSequence() || node.size() != 2) {
        return false;
      }
      
      size.width  = node[0].as<decltype(size.width)>();
      size.height = node[1].as<decltype(size.height)>();
      
      return size.width > 0 && size.height > 0;
    }
  };
}

void Res::TextureAtlasSerializer::importAtlas(Ogre::DataStreamPtr &stream, TextureAtlas *atlas) {
  assert(stream->isReadable());
  assert(atlas);
  
  try {
    const YAML::Node doc = YAML::Load(stream->getAsString());
    
    if (const YAML::Node &head = doc["head"]) {
      if (const YAML::Node &texSize = head["texture size"]) {
        atlas->textureSize = texSize.as<decltype(atlas->textureSize)>();
        YAML::convert<Res::TextureAtlas::Sprite>::textureSize = atlas->textureSize;
      } else {
        LOG_ERROR(RESOURCES, "Texture atlas doesn't contain texture size");
        return;
      }
    } else {
      LOG_ERROR(RESOURCES, "Texture atlas doesn't contain head section");
      return;
    }
    
    if (const YAML::Node &body = doc["body"]) {
      atlas->sprites = body.as<decltype(atlas->sprites)>();
    } else {
      LOG_ERROR(RESOURCES, "Texture atlas doesn't contain body section");
      return;
    }
    
  } catch (YAML::Exception &e) {
    LOG_ERROR(RESOURCES, "%s", e.what());
  }
}

void Res::TextureAtlasSerializer::exportAtlas(const TextureAtlas *atlas, const Ogre::String &string) {
  Ogre::DataStreamPtr stream(new Ogre::FileStreamDataStream(new std::ifstream(string)));
  exportAtlas(atlas, stream);
}

YAML::Emitter &operator<<(YAML::Emitter &out, const Res::TextureAtlas::Size &size) {
  return out << YAML::BeginSeq << size.width << size.height << YAML::EndSeq;
}

YAML::Emitter &operator<<(YAML::Emitter &out, const Res::TextureAtlas::Sprite &sprite) {
  return out << YAML::BeginSeq <<
    sprite.left <<
    sprite.top <<
    sprite.right <<
    sprite.bottom <<
  YAML::EndSeq;
}

void Res::TextureAtlasSerializer::exportAtlas(const TextureAtlas *atlas, Ogre::DataStreamPtr &stream) {
  assert(atlas);
  assert(stream->isWriteable());
  
  YAML::convert<Res::TextureAtlas::Sprite>::textureSize = atlas->textureSize;
  YAML::Emitter emitter;
  emitter <<
  YAML::Key << "head" << YAML::Value << YAML::BeginMap <<
    YAML::Key << "texture size" << YAML::Value << atlas->textureSize <<
  YAML::EndMap <<
  YAML::Key << "body" << YAML::Value << YAML::BeginMap;
  for (auto i = atlas->sprites.begin(); i != atlas->sprites.end(); i++) {
    emitter << YAML::Key << i->first << YAML::Value << i->second;
  }
  emitter << YAML::EndMap;
  stream->write(emitter.c_str(), emitter.size());
}
