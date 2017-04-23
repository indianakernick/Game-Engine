//
//  texture atlas.hpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_texture_atlas_hpp
#define engine_resource_handles_texture_atlas_hpp

#include "../../Application/ogre.pch"

namespace Res {
  class TextureAtlas final : public Ogre::Resource {
  friend class TextureAtlasSerializer;
  public:
    struct Sprite {
      //    x0    y0   x1     y1
      float left, top, right, bottom;
    };
    struct Size {
      uint32_t width;
      uint32_t height;
    };
    
    TextureAtlas(Ogre::ResourceManager *,
                 const Ogre::String &,
                 Ogre::ResourceHandle,
                 const Ogre::String &,
                 bool,
                 Ogre::ManualResourceLoader *);
    ~TextureAtlas();
    
    Sprite getSprite(const std::string &) const;
    
  private:
    static const size_t ESTIMATE_SPRITE_NAME_LENGTH;
  
    std::map<std::string, Sprite> sprites;
    Size textureSize;
  
    void loadImpl() override;
    void unloadImpl() override;
    size_t calculateSize() const override;
  };
  
  using TextureAtlasPtr = Ogre::SharedPtr<TextureAtlas>;
}

#endif
