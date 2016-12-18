//
//  sdl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl.hpp"

#ifdef _SDL_H

void Libraries::SDL::init() {
  SDL_Init(SDL_INIT_EVERYTHING);
}

void Libraries::SDL::quit() {
  SDL_Quit();
}

Window::Ptr Libraries::SDL::makeWindow() {
  return std::make_shared<Windows::SDLOpenGL>();
}

std::string Libraries::SDL::getSaveDir(std::string companyName, std::string appName) {
  return SDL_GetPrefPath(companyName.c_str(), appName.c_str());
}

uint64_t Libraries::SDL::getSystemRAM() {
  return SDL_GetSystemRAM() * Math::Byte::MEGA_ONE;
}

#endif