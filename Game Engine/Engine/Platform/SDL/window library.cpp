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
    LOG_INFO(PLATFORM, "SDL initialized successfully");
  } else {
    LOG_ERROR(PLATFORM, "SDL failed to initialize: %s", SDL_GetError());
  }
}

void Platform::quitLib() {
  SDL_Quit();
}

Platform::InputManager::Ptr Platform::createInputManager(Window::Ptr window) {
  return std::make_shared<InputManagerImpl>(window->size());
}

#endif
