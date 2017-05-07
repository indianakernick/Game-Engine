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
#include "../../Game View/Human/types.hpp"

namespace Res {
  class TextureAtlas final : public Ogre::Resource {
  friend class TextureAtlasSerializer;
  public:
    enum class Type {
      IMAGE,
      FONT
    };
    
    struct FontMetrics {
      int lineHeight;
      int minY;
      int maxY;
    };
    
    struct GlyphMetrics {
      UI::PointPx bearing;
      UI::PointPx size;
      int advance;
    };
    
    struct Glyph {
      UI::TexCoords glyph;
      GlyphMetrics metrics;
    };
    
    static const UI::TexCoords ZERO_SPRITE;
    static const Glyph ZERO_GLYPH;
    
    static bool isZero(const Glyph &);
    
    TextureAtlas(
      Ogre::ResourceManager *,
      const Ogre::String &,
      Ogre::ResourceHandle,
      const Ogre::String &,
      bool,
      Ogre::ManualResourceLoader *
    );
    ~TextureAtlas();
    
    Type getType() const;
    UI::PointPx getTextureSize() const;
    bool hasWhitepixel() const;
    UI::TexCoords getWhitepixel() const;
    UI::TexCoords getSprite(const std::string &) const;
    Glyph getGlyph(char) const;
    FontMetrics getFontMetrics() const;
    int getKerning(char, char) const;
    
  private:
    static const size_t ESTIMATE_SPRITE_NAME_LENGTH;
  
    //always valid
    Type type;
    UI::PointPx textureSize;
    
    //valid when type is IMAGE
    UI::TexCoords whitepixel;
    std::map<std::string, UI::TexCoords> sprites;
    
    //valid when type is FONT
    std::vector<UI::TexCoords> glyphs;
    std::vector<GlyphMetrics> metrics;
    std::vector<int> kerning;
    FontMetrics fontMetrics;
    char begin;
    char end;
  
    void loadImpl() override;
    void unloadImpl() override;
    size_t calculateSize() const override;
  };
  
  using TextureAtlasPtr = Ogre::SharedPtr<TextureAtlas>;
}

#endif
