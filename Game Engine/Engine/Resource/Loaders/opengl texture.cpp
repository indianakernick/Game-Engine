//
//  opengl texture.cpp
//  Game Engine
//
//  Created by Indi Kernick on 17/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "opengl texture.hpp"

#ifdef __gl_h_

bool Resource::Loaders::TextureOpenGL::canLoad(const std::string &fileExt) {
  static const std::string EXT[] = {"jpg","jpeg","png","bmp","psd","tga","gif",
                                    "hdr","pic","pgm","ppm"};
  for (const std::string &ext : EXT) {
    if (fileExt == ext) {
      return true;
    }
  }
  return false;
}

size_t Resource::Loaders::TextureOpenGL::getSize(const Memory::Buffer) {
  ///The texture is in VRAM so it doesn't take up any space in RAM
  return 0;
}

bool Resource::Loaders::TextureOpenGL::useRaw() {
  return false;
}

Resource::Desc::Ptr Resource::Loaders::TextureOpenGL::process(const Memory::Buffer file, Memory::Buffer) {
  Geometry::Size size;
  Byte *pixels = stbi_load_from_memory(file.begin(),
                                       static_cast<int>(file.size()),
                                       &size.w, &size.h,
                                       nullptr, STBI_rgb_alpha);
  
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.w, size.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  stbi_image_free(pixels);
  
  return std::make_shared<Descs::TextureOpenGL>(textureID);
}

#endif
