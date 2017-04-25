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

namespace Res {
  class TextureAtlasSerializer final : public Ogre::Serializer {
  public:
    TextureAtlasSerializer() = default;
    ~TextureAtlasSerializer() = default;
    
    void importAtlas(Ogre::DataStreamPtr &, TextureAtlas *);
    void exportAtlas(const TextureAtlas *, const Ogre::String &);
    void exportAtlas(const TextureAtlas *, Ogre::DataStreamPtr &);
  
  private:
    void importImageAtlas(const YAML::Node &, TextureAtlas *);
    void importFontAtlas(const YAML::Node &, TextureAtlas *);
  };
}

#endif
