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

const std::string &TextureLoaderOpenGL::getName() {
  static const std::string NAME = "OpenGL texture";
  return NAME;
}

bool TextureLoaderOpenGL::canLoad(const std::string &fileExt) {
  static const std::string EXT[11] = {"jpg","jpeg","png","bmp",
                                      "psd","tga","gif",
                                      "hdr","pic","pgm","ppm"};
  
  return std::any_of(EXT, EXT + 11, [&fileExt](const std::string &ext) {
    return fileExt == ext;
  });
}

Handle::Ptr TextureLoaderOpenGL::load(const ID &id) {
  int width, height;
  Byte *pixels = stbi_load_from_file(openFile(id),
                                     &width, &height,
                                     nullptr, STBI_rgb_alpha);
  
  if (pixels == nullptr) {
    LOG_ERROR(RESOURCES, "Failed to load texture \"%s\". STB Image - %s",
                         id.getPathC(), stbi_failure_reason());
    return nullptr;
  } else {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    stbi_image_free(pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
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

#endif
