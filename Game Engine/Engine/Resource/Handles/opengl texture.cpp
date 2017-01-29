//
//  opengl texture.cpp
//  Game Engine
//
//  Created by Indi Kernick on 17/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "opengl texture.hpp"

#ifdef USE_OPENGL

Res::TextureOpenGL::TextureOpenGL(GLuint textureID)
  : textureID(textureID) {}

Res::TextureOpenGL::~TextureOpenGL() {
  glDeleteTextures(1, &textureID);
}

GLuint Res::TextureOpenGL::getID() const {
  return textureID;
}

#endif
