//
//  opengl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 28/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_opengl_hpp
#define engine_application_opengl_hpp

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#ifdef NDEBUG

#define CHECK_OPENGL_ERROR

#else

#define CHECK_OPENGL_ERROR \
for (GLenum error; (error = glGetError()) != GL_NO_ERROR;) {\
  printf("OpenGL error: %s\n",gluErrorString(error));\
  assert(false);\
}\

#endif

#endif
