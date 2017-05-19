//
//  texture atlas.hpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_serializers_texture_atlas_hpp
#define engine_resource_serializers_texture_atlas_hpp

#include "../Handles/texture atlas.hpp"
#include "../../Utils/logger.hpp"
#include <yaml-cpp/yaml.h>
#include "../../Game View/Human/conversions.hpp"
#include "../exceptions.hpp"

namespace Res {
  class InvalidTextureAtlas : public InvalidResource {
  public:
    explicit InvalidTextureAtlas(const std::string &);
  };

  class TextureAtlasSerializer final : public Ogre::Serializer {
  public:
    TextureAtlasSerializer() = default;
    ~TextureAtlasSerializer() = default;
    
    void importAtlas(Ogre::DataStreamPtr &, TextureAtlas *);
  
  private:
    void importImageAtlas(const YAML::Node &, TextureAtlas *);
    void importFontAtlas(const YAML::Node &, TextureAtlas *);
  };
}

#endif
