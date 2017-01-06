//
//  sdl opengl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl opengl.hpp"

#ifdef _SDL_H

void Windows::SDLOpenGL::open(const Desc &desc) {
  uint32_t resizable = desc.resizable * SDL_WINDOW_RESIZABLE;
  uint32_t fullscreen = desc.fullscreen * SDL_WINDOW_FULLSCREEN;
  
  title = desc.title;
  size = desc.size;
  
  window = SDL_CreateWindow(title.c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            size.w, size.h,
                            SDL_WINDOW_SHOWN |
                            SDL_WINDOW_OPENGL |
                            resizable |
                            fullscreen);
  
  if (window) {
    Log::write(Log::RENDERING, Log::INFO, "Successfully created window");
  } else {
    Log::write(Log::RENDERING, Log::ERROR, "Failed to create window: %s", SDL_GetError());
  }
  
  Log::write(Log::RENDERING, Log::VERBOSE, "Window title: \"%s\", size: %i,%i", title.c_str(), size.w, size.h);
}

Renderer::Ptr Windows::SDLOpenGL::createRenderer(const Renderer::Desc &desc) {
  auto renderer = std::make_shared<Renderers::SDLOpenGL>();
  renderer->init(this, desc);
  return renderer;
}

Input::Manager::Ptr Windows::SDLOpenGL::createInputManager() {
  return std::make_shared<Input::Managers::SDL>(size);
}

void Windows::SDLOpenGL::close() {
  SDL_DestroyWindow(window);
  window = nullptr;
}

void Windows::SDLOpenGL::changeTitle(std::string newTitle) {
  title = newTitle;
  SDL_SetWindowTitle(window, title.c_str());
}

void Windows::SDLOpenGL::resize(Geometry::Size newSize) {
  size = newSize;
  SDL_SetWindowSize(window, size.w, size.h);
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Windows::SDLOpenGL::relMouse(bool status) {
  SDL_SetRelativeMouseMode(static_cast<SDL_bool>(status));
}

bool Windows::SDLOpenGL::relMouse() {
  return SDL_GetRelativeMouseMode();
}

void Windows::SDLOpenGL::captureMouse(bool status) {
  mouseCaptured = status;
  SDL_CaptureMouse(static_cast<SDL_bool>(status));
}

bool Windows::SDLOpenGL::captureMouse() {
  return mouseCaptured;
}

void Windows::SDLOpenGL::fullscreen(bool status) {
  fullscreenEnabled = status;
  SDL_SetWindowFullscreen(window, status * SDL_WINDOW_FULLSCREEN);
}

bool Windows::SDLOpenGL::fullscreen() {
  return fullscreenEnabled;
}

#endif
