//
//  window library.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "window library.hpp"

#ifdef USE_SDL

void Platform::initLib() {
  if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) == 0) {
    LOG_INFO(RENDERING, "SDL initialized successfully");
  } else {
    LOG_ERROR(RENDERING, "SDL failed to initialize: %s", SDL_GetError());
  }
}

void Platform::quitLib() {
  SDL_Quit();
}

Platform::InputManager::Ptr Platform::createInputManager(Window::Ptr window) {
  return std::make_shared<InputManagerImpl>(window->size());
}

std::string Platform::getSaveDir(std::string companyName, std::string appName) {
  char *cstr = SDL_GetPrefPath(companyName.c_str(), appName.c_str());
  std::string str(cstr);
  SDL_free(cstr);
  return str;
}

uint64_t Platform::getSystemRAM() {
  return SDL_GetSystemRAM() * Math::Byte::MEGA_ONE;
}

glm::vec2 Platform::getDisplayDPI() {
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
