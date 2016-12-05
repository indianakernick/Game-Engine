//
//  manager factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager factory.hpp"

Input::Manager::Ptr Input::makeManager() {
  #ifdef _SDL_events_h
  return std::make_shared<Managers::SDL>();
  #else
  return nullptr;
  #endif
}
