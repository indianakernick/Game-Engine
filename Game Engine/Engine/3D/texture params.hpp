//
//  texture params.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_texture_params_hpp
#define engine_3d_texture_params_hpp

#include <cstdint>
#include <glm/vec4.hpp>
#include "../Utils/combine.hpp"

namespace Graphics3D {
  ///Texture wrapping mode
  enum class TexWrap : uint8_t {
    ///Clamp to edge of texture
    CLAMP,
    ///Clamp to border and use border color
    CLAMP_BORDER,
    ///Repeat the texture
    REPEAT,
    ///Repeat and mirror odd repeatitions of the texture
    REPEAT_MIRROR
  };
  
  ///Texture minification filter
  enum class TexMin : uint8_t {
    ///Nearest pixel
    NEAREST,
    ///Linear pixel
    LINEAR,
    ///Nearest pixel, nearest mipmap
    NEAREST_MIPMAP_NEAREST,
    ///Linear pixel, nearest mipmap
    LINEAR_MIPMAP_NEAREST,
    ///Nearest pixel, linear mipmap
    NEAREST_MIPMAP_LINEAR,
    ///linear pixel, linear mipmap
    LINEAR_MIPMAP_LINEAR,
  };
  
  ///Texture magnification filter
  enum class TexMag : uint8_t {
    ///Nearest pixel
    NEAREST,
    ///Linear pixel
    LINEAR
  };
  
  ///Anisotropic filtering is disabled
  static const float AF_DISABLED = 1.0f;
  
  struct TexParams {
    ///Border color used if CLAMP_BORDER wrapping mode is used
    glm::vec4 border;
    ///Horizontal wrapping mode
    TexWrap wrapS = TexWrap::REPEAT;
    ///Vertical wrapping mode
    TexWrap wrapT = TexWrap::REPEAT;
    ///Minification filter
    TexMin min = TexMin::LINEAR;
    ///Magnification filter
    TexMag mag = TexMag::LINEAR;
    ///Anisotropic filtering (disabled by default).
    float af = 1.0f;
    ///Whether of not the texture should be inverted before use
    bool invert = false;
    ///Whether or not the texture has an alpha channel
    bool hasAlpha = true;
    
    ///Disables Anisotropic filtering (disabled by default)
    void disableAF();
    ///Checks whether Anisotropic filtering enabled
    bool afEnabled() const;
    ///Sets both wrapS and wrapT to the same wrapping mode
    void setWrap(const TexWrap);
    
    bool operator==(const TexParams &) const;
    bool operator!=(const TexParams &) const;
  };
};

template <>
struct std::hash<glm::vec4> {
  size_t operator()(const glm::vec4 &) const;
};

template <>
struct std::hash<Graphics3D::TexParams> {
  size_t operator()(const Graphics3D::TexParams &) const;
};

#endif
