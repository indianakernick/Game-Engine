//
//  sdl opengl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl opengl.hpp"

#if defined(USE_SDL) && defined(USE_OPENGL)

void Renderers::SDLOpenGL::init(Window *windowInterface, const Desc &desc) {
  Windows::SDLOpenGL *sdlOpengl = dynamic_cast<Windows::SDLOpenGL *>(windowInterface);
  assert(sdlOpengl);
  window = sdlOpengl->window;
  clearColor = desc.clearColor;
  
  context = SDL_GL_CreateContext(window);
  
  if (context) {
    Log::write(Log::RENDERING, Log::INFO, "OpenGL context created successfully");
  } else {
    Log::write(Log::RENDERING, Log::ERROR, "Failed to create OpenGL context: %s", SDL_GetError());
  }
  
  Log::write(Log::RENDERING, Log::VERBOSE, "Depth bits: %i, stencil bits: %i, color bits %i", desc.depthBits, desc.stencilBits, desc.colorBits);
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, desc.depthBits);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, desc.stencilBits);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, desc.colorBits);
  
  //I think it would make more sense to put this in the Library class but glew
  //has to be initialized after a context has been initialized
  //i don't know if it has to be initialized for each context
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError == GLEW_OK) {
    Log::write(Log::RENDERING, Log::INFO, "GLEW initialized successfully");
  } else {
    Log::write(Log::RENDERING, Log::ERROR, "Failed to intialized GLEW: %s", glewGetErrorString(glewError));
  }
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
}

void Renderers::SDLOpenGL::quit() {
  SDL_GL_DeleteContext(context);
}

void Renderers::SDLOpenGL::preRender() {
  glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
  glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    Log::writeNow(Log::RENDERING, Log::ERROR, "Pre-render failed: %s", gluErrorString(error));
  }
}

void Renderers::SDLOpenGL::postRender() {
  SDL_GL_SwapWindow(window);
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    Log::writeNow(Log::RENDERING, Log::ERROR, "Post-render failed: %s", gluErrorString(error));
  }
}

#endif
