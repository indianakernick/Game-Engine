//
//  texture.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture.hpp"

#ifdef USE_OPENGL

using namespace Platform;

TextureImpl::TextureImpl(GLuint id)
  : id(id) {
  assert(id);
}

TextureImpl::~TextureImpl() {
  glDeleteTextures(1, &id);
}

GLuint TextureImpl::getID() const {
  return id;
}

#endif
