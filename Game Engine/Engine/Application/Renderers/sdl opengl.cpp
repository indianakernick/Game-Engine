//
//  sdl opengl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl opengl.hpp"

#ifdef _SDL_opengl_h

void Renderers::SDLOpenGL::init(Window *windowInterface, const Desc &desc) {
  Windows::SDLOpenGL *sdlOpengl = dynamic_cast<Windows::SDLOpenGL *>(windowInterface);
  assert(sdlOpengl);
  window = sdlOpengl->window;
  clearColor = desc.clearColor;
  
  context = SDL_GL_CreateContext(window);
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, desc.depthBits);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, desc.stencilBits);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, desc.colorBits);
}

void Renderers::SDLOpenGL::quit() {
  SDL_GL_DeleteContext(context);
}

void Renderers::SDLOpenGL::preRender() {
  glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderers::SDLOpenGL::postRender() {
  SDL_GL_SwapWindow(window);
}

#endif
