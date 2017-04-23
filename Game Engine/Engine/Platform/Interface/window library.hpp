//
//  window library.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_window_library_hpp
#define engine_platform_interface_window_library_hpp

#include "input manager.hpp"
#include "window manager.hpp"
#include "../../Application/ogre.pch"

namespace Platform {
  void initLib();
  void quitLib();
  Ogre::RenderWindow *createRenderWindow(std::weak_ptr<Window>, Ogre::Root *);
  WindowManager::Ptr createWindowManager();
  InputManager::Ptr createInputManager(WindowManager::Ptr);
}

#endif
