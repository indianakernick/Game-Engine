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

#endif
