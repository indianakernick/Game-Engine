//
//  sdl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl.hpp"

#ifdef USE_SDL

void Libraries::SDL::init() {
  if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) == 0) {
    LOG_INFO(RENDERING, "SDL initialized successfully");
  } else {
    LOG_ERROR(RENDERING, "SDL failed to initialize: %s", SDL_GetError());
  }
}

void Libraries::SDL::quit() {
  SDL_Quit();
}

Window::Ptr Libraries::SDL::makeWindow() {
  return std::make_shared<Windows::SDLOpenGL>();
}

std::string Libraries::SDL::getSaveDir(std::string companyName, std::string appName) {
  char *cstr = SDL_GetPrefPath(companyName.c_str(), appName.c_str());
  std::string str(cstr);
  SDL_free(cstr);
  return str;
}

uint64_t Libraries::SDL::getSystemRAM() {
  return SDL_GetSystemRAM() * Math::Byte::MEGA_ONE;
}

glm::vec2 Libraries::SDL::getDisplayDPI() {
  /*
  This fails on my system for some reason. 
  So I got a ruler out and measured the DPI myself!
  
  glm::vec2 dpi;
  if (SDL_GetDisplayDPI(0, nullptr, &dpi.x, &dpi.y) == -1) {
    LOG_ERROR(RENDERING, "Failed to get display DPI: %s", SDL_GetError());
  }
  return dpi;*/
  return {128.0f, 128.0f};
}

#endif
