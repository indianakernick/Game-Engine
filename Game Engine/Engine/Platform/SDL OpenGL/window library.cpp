//
//  window library.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "window library.hpp"

#ifdef USE_SDL_OPENGL

Platform::Window::Ptr Platform::openWindow(const Window::Desc &desc) {
  const uint32_t resizable = boolEnable(desc.resizable, SDL_WINDOW_RESIZABLE);
  const uint32_t fullscreen = boolEnable(desc.fullscreen, SDL_WINDOW_FULLSCREEN);
  
  SDL_Window *window = SDL_CreateWindow(desc.title.c_str(),
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        desc.size.x, desc.size.y,
                                        SDL_WINDOW_SHOWN |
                                        SDL_WINDOW_OPENGL |
                                        resizable |
                                        fullscreen);
  
  if (window) {
    LOG_INFO(PLATFORM, "Successfully created window");
  } else {
    LOG_ERROR(PLATFORM, "Failed to create window: %s", SDL_GetError());
  }
  
  LOG_INFO(PLATFORM,
    "Window title: \"%s\", size: %i,%i",
    desc.title.c_str(), desc.size.x, desc.size.y);
  
  return std::make_shared<WindowImpl>(window, false, desc.fullscreen);
}

void configureContext(const Platform::RenderingContext::Desc &desc) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  int flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
  #ifndef NDEBUG
  flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
  #endif
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, flags);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, desc.depthBits);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, desc.stencilBits);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, desc.colorBits);
  
  LOG_INFO(PLATFORM,
    "Color bits %i, depth bits: %i, stencil bits: %i",
    desc.colorBits, desc.depthBits, desc.stencilBits);
  
  CHECK_OPENGL_ERROR();
}

SDL_GLContext makeContext(SDL_Window *window) {
  SDL_GLContext context = SDL_GL_CreateContext(window);
  
  if (context) {
    LOG_INFO(PLATFORM, "OpenGL context created successfully");
  } else {
    LOG_ERROR(PLATFORM, "Failed to create OpenGL context: %s", SDL_GetError());
  }
  
  return context;
}

void initGlew() {
  glewExperimental = GL_TRUE;
  const GLenum glewError = glewInit();
  if (glewError == GLEW_OK) {
    LOG_INFO(PLATFORM, "GLEW initialized successfully");
  } else {
    LOG_ERROR(PLATFORM,
      "Failed to intialized GLEW: %s",
      glewGetErrorString(glewError));
  }
}

void setGLState(const Platform::RenderingContext::Desc &desc) {
  glClearColor(desc.clearColor.r,
               desc.clearColor.g,
               desc.clearColor.b,
               desc.clearColor.a);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_FRAMEBUFFER_SRGB);
  
  CHECK_OPENGL_ERROR();
}

void logContextInfo() {
  LOG_INFO(PLATFORM, "OpenGL version: %s", glGetString(GL_VERSION));
  LOG_INFO(PLATFORM, "GLSL version:   %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  LOG_INFO(PLATFORM, "Vendor:         %s", glGetString(GL_VENDOR));
  LOG_INFO(PLATFORM, "Renderer:       %s", glGetString(GL_RENDERER));
  
  CHECK_OPENGL_ERROR();
}

void logExtensions() {
  std::string extensions;
  GLint numExtensions;
  glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
  for (GLint i = 0; i < numExtensions; i++) {
    extensions += reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i));
    extensions += '\n';
  }
  
  if (numExtensions) {
    LOG_INFO(PLATFORM, "Extensions:\n%s", extensions.c_str());
  }
  
  CHECK_OPENGL_ERROR();
}

Platform::RenderingContext::Ptr Platform::createRenderingContext(
  Window::Ptr window,
  const RenderingContext::Desc &desc
) {
  configureContext(desc);
  std::shared_ptr<WindowImpl> impl = std::dynamic_pointer_cast<WindowImpl>(window);
  assert(impl);
  SDL_GLContext context = makeContext(impl->getWindow());
  //glew has to be initialized after a context has been initialized
  //i don't know if it has to be initialized for each context
  initGlew();
  setGLState(desc);
  logContextInfo();
  logExtensions();
  
  CHECK_OPENGL_ERROR();
  
  return std::make_shared<RenderingContextImpl>(impl->getWindow(), context);
}

#endif
