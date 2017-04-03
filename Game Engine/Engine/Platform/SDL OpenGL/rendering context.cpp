//
//  rendering context.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering context.hpp"

#ifdef USE_SDL_OPENGL

using namespace Platform;

RenderingContextImpl::RenderingContextImpl(SDL_Window *window, SDL_GLContext context)
  : window(window), context(context) {}

RenderingContextImpl::~RenderingContextImpl() {
  SDL_GL_DeleteContext(context);
}

void RenderingContextImpl::preRender() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  CHECK_OPENGL_ERROR();
}

void RenderingContextImpl::postRender() {
  SDL_GL_SwapWindow(window);
  CHECK_OPENGL_ERROR();
}

#endif
