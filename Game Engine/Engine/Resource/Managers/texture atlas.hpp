//
//  texture atlas.hpp
//  Game Engine
//
//  Created by Indi Kernick on 21/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_managers_texture_atlas_hpp
#define engine_resource_managers_texture_atlas_hpp

#include "../Handles/texture atlas.hpp"

namespace Res {
  class TextureAtlasManager final : public Ogre::ResourceManager,
                                    public Ogre::Singleton<TextureAtlasManager> {
  public:
    TextureAtlasManager();
    ~TextureAtlasManager();
    
  private:
    Ogre::Resource *createImpl(const Ogre::String &,
                               Ogre::ResourceHandle,
                               const Ogre::String &,
                               bool,
                               Ogre::ManualResourceLoader *,
                               const Ogre::NameValuePairList *) override;
    
  };
}

#endif
