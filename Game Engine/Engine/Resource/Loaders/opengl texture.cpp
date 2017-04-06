//
//  opengl texture.cpp
//  Game Engine
//
//  Created by Indi Kernick on 17/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "opengl texture.hpp"

#ifdef USE_OPENGL

using namespace Res;
using namespace Graphics3D;

const std::string &TextureLoaderOpenGL::getName() const {
  static const std::string NAME = "OpenGL texture";
  return NAME;
}

bool TextureLoaderOpenGL::canLoad(std::experimental::string_view ext) const {
  static const char *EXTS[] = {
    "jpg","jpeg","png","bmp","psd","tga","gif","hdr","pic","pgm","ppm"
  };
  return hasExt(EXTS, ext);
}

Handle::Ptr TextureLoaderOpenGL::load(const ID &id) const {
  const Any &data = id.getData();
  TexParams params;
  if (data.is<Graphics3D::TexParams>()) {
    params = data.as<Graphics3D::TexParams>();
  }
  
  int width, height, format = params.hasAlpha ? STBI_rgb_alpha : STBI_rgb;
  Byte *pixels = stbi_load_from_file(openFile(id).get(),
                                     &width, &height,
                                     nullptr, format);
  
  if (pixels == nullptr) {
    LOG_ERROR(RESOURCES, "Failed to load texture \"%s\". STB Image - %s",
                         id.getPathC(), stbi_failure_reason());
    return nullptr;
  } else {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    setTexParams(params);
    
    if (params.invert) {
      const Byte *size = pixels + width * height * format;
      for (Byte *p = pixels; p < size; p++) {
        *p = 255 - *p;
      }
    }
    
    if (params.hasAlpha) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA,
                   width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB,
                   width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }
    stbi_image_free(pixels);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    if (!glIsTexture(textureID)) {
      LOG_ERROR(RESOURCES,
        "Failed to load texture \"%s\". Could not create texture",
        id.getPathC());
    }
    
    Handle::Ptr handle = std::make_shared<TextureOpenGL>(textureID);
    handle->setSize(width * height * 4);
    return handle;
  }
}

namespace {
  GLenum toGL(const TexWrap wrap) {
    switch (wrap) {
      case TexWrap::CLAMP:
        return GL_CLAMP;
      case TexWrap::CLAMP_BORDER:
        return GL_CLAMP_TO_BORDER;
      case TexWrap::REPEAT:
        return GL_REPEAT;
      case TexWrap::REPEAT_MIRROR:
        return GL_MIRRORED_REPEAT;
      default:
        assert(false);
    }
  }

  GLenum toGL(const TexMin min) {
    switch (min) {
      case TexMin::NEAREST:
        return GL_NEAREST;
      case TexMin::LINEAR:
        return GL_LINEAR;
      case TexMin::NEAREST_MIPMAP_NEAREST:
        return GL_NEAREST_MIPMAP_NEAREST;
      case TexMin::LINEAR_MIPMAP_NEAREST:
        return GL_LINEAR_MIPMAP_NEAREST;
      case TexMin::NEAREST_MIPMAP_LINEAR:
        return GL_NEAREST_MIPMAP_LINEAR;
      case TexMin::LINEAR_MIPMAP_LINEAR:
        return GL_LINEAR_MIPMAP_LINEAR;
      default:
        assert(false);
    }
  }

  GLenum toGL(const TexMag mag) {
    switch (mag) {
      case TexMag::NEAREST:
        return GL_NEAREST;
      case TexMag::LINEAR:
        return GL_LINEAR;
      default:
        assert(false);
    }
  }
}

void TextureLoaderOpenGL::setTexParams(const Graphics3D::TexParams params) {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGL(params.wrapS));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGL(params.wrapT));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGL(params.min));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGL(params.mag));
  if (params.wrapS == TexWrap::CLAMP_BORDER ||
      params.wrapT == TexWrap::CLAMP_BORDER) {
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &params.border.r);
  }
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, params.af);
}

#endif
