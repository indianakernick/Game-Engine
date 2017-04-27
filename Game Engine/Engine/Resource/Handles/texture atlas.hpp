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
#include <glm/vec2.hpp>

namespace Res {
  class TextureAtlas final : public Ogre::Resource {
  friend class TextureAtlasSerializer;
  public:
    struct Sprite {
      //    x0    y0   x1     y1
      float left, top, right, bottom;
    };
    enum class Type {
      IMAGE,
      FONT
    };
    struct GlyphMetrics {
      glm::ivec2 bearing;
      glm::ivec2 size;
      int advance;
    };
    struct Glyph {
      Sprite glyph;
      GlyphMetrics metrics;
    };
    
    TextureAtlas(Ogre::ResourceManager *,
                 const Ogre::String &,
                 Ogre::ResourceHandle,
                 const Ogre::String &,
                 bool,
                 Ogre::ManualResourceLoader *);
    ~TextureAtlas();
    
    Type getType() const;
    Sprite getSprite(const std::string &) const;
    Glyph getGlyph(wchar_t) const;
    int getLineHeight() const;
    int getKerning(wchar_t, wchar_t) const;
    
  private:
    static const size_t ESTIMATE_SPRITE_NAME_LENGTH;
  
    //always valid
    Type type;
    glm::ivec2 textureSize;
    
    //valid when type is IMAGE
    std::map<std::string, Sprite> sprites;
    
    //valid when type is FONT
    wchar_t beginChar;
    wchar_t endChar;
    int lineHeight;
    std::vector<Sprite> glyphs;
    std::vector<GlyphMetrics> metrics;
    std::vector<int> kerning;
  
    void loadImpl() override;
    void unloadImpl() override;
    size_t calculateSize() const override;
  };
  
  using TextureAtlasPtr = Ogre::SharedPtr<TextureAtlas>;
}

#endif
