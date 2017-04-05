//
//  system info.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "system info.hpp"

#ifdef USE_SDL

std::string Platform::getSaveDir(const std::string &companyName,
                                 const std::string &appName) {
  char *cstr = SDL_GetPrefPath(companyName.c_str(), appName.c_str());
  std::string str(cstr);
  SDL_free(cstr);
  return str;
}

uint64_t Platform::getRAM() {
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
