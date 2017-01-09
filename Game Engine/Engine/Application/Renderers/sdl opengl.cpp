//
//  sdl opengl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl opengl.hpp"

#if defined(USE_SDL) && defined(USE_OPENGL)

/*std::string getSourceStr(GLenum source) {
  switch (source) {
    case GL_DEBUG_SOURCE_API:
      return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      return "Window system";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      return "Shader compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      return "Third party";
    case GL_DEBUG_SOURCE_APPLICATION:
      return "Application";
    case GL_DEBUG_SOURCE_OTHER:
      return "Other";
    default:
      return "";
  }
}

std::string getTypeStr(GLenum type) {
  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      return "Deprecated behaviour";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      return "Undefined behaviour";
    case GL_DEBUG_TYPE_PORTABILITY:
      return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE:
      return "Performance";
    case GL_DEBUG_TYPE_MARKER:
      return "Marker";
    case GL_DEBUG_TYPE_PUSH_GROUP:
      return "Push group";
    case GL_DEBUG_TYPE_POP_GROUP:
      return "Pop group";
    case GL_DEBUG_TYPE_OTHER:
      return "Other";
    default:
      return "";
  }
}

std::string getSeverityStr(GLenum severity) {
  switch (severity) {
    case GL_DEBUG_SEVERITY_LOW:
      return "Low";
    case GL_DEBUG_SEVERITY_MEDIUM:
      return "Medium";
    case GL_DEBUG_SEVERITY_HIGH:
      return "High";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      return "Notification";
    default:
      return "";
  }
}

extern "C" {

void GLAPIENTRY errorCallback(GLenum source,
                              GLenum type,
                              GLuint id,
                              GLenum severity,
                              GLsizei,
                              const GLchar *message,
                              const void *) {
  std::string logMessage = "\n";
  logMessage += "Source:   " + getSourceStr(source) + "\n";
  logMessage += "Type:     " + getTypeStr(type) + "\n";
  logMessage += "ID:       " + std::to_string(id) + "\n";
  logMessage += "Severity: " + getSeverityStr(severity) + "\n";
  logMessage += "Message:  " + std::string(message) + "\n";
  Log::writeNow(Log::RENDERING, Log::ERROR, logMessage.c_str());
  
  if (severity == GL_DEBUG_SEVERITY_HIGH) {
    assert(false);
  }
}

}*/

void Renderers::SDLOpenGL::init(Window *windowInterface, const Desc &desc) {
  Windows::SDLOpenGL *sdlOpengl = dynamic_cast<Windows::SDLOpenGL *>(windowInterface);
  assert(sdlOpengl);
  window = sdlOpengl->window;
  clearColor = desc.clearColor;
  
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
  
  context = SDL_GL_CreateContext(window);
  
  if (context) {
    LOG_INFO(RENDERING, "OpenGL context created successfully");
  } else {
    LOG_ERROR(RENDERING, "Failed to create OpenGL context: %s", SDL_GetError());
  }
  
  LOG_DEBUG(RENDERING, "Depth bits: %i, stencil bits: %i, color bits %i", desc.depthBits, desc.stencilBits, desc.colorBits);
  
  //I think it would make more sense to put this in the Library class but glew
  //has to be initialized after a context has been initialized
  //i don't know if it has to be initialized for each context
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError == GLEW_OK) {
    LOG_INFO(RENDERING, "GLEW initialized successfully");
  } else {
    LOG_ERROR(RENDERING, "Failed to intialized GLEW: %s", glewGetErrorString(glewError));
  }
  
  //this doesn't work on MacOS because it only supports OpenGL 4.1
  
  /*
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(errorCallback, nullptr);
  glDebugMessageControl(GL_DONT_CARE,
                        GL_DONT_CARE,
                        GL_DONT_CARE,
                        0,
                        nullptr,
                        true);
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    Log::writeNow(Log::RENDERING, Log::ERROR,
      "There was an error creating the debug mesage callback %s", gluErrorString(error));
  }
  */
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  //glCullFace(GL_FRONT_FACE);
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING,
      "Error intializing OpenGL %s", gluErrorString(error));
  }
  
  LOG_INFO(RENDERING, "OpenGL version: %s", glGetString(GL_VERSION));
  LOG_INFO(RENDERING, "GLSL version:   %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  LOG_INFO(RENDERING, "Vendor:         %s", glGetString(GL_VENDOR));
  LOG_INFO(RENDERING, "Renderer:       %s", glGetString(GL_RENDERER));
}

void Renderers::SDLOpenGL::quit() {
  SDL_GL_DeleteContext(context);
}

void Renderers::SDLOpenGL::preRender() {
  glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
  glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING, "Pre-render failed: %s", gluErrorString(error));
  }
}

void Renderers::SDLOpenGL::postRender() {
  SDL_GL_SwapWindow(window);
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING, "Post-render failed: %s", gluErrorString(error));
  }
}

#endif
