//
//  window library.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_window_library_hpp
#define engine_platform_interface_window_library_hpp

#include "window.hpp"
#include "input manager.hpp"
#include <Ogre/OgreRoot.h>

namespace Platform {
  void initLib();
  void quitLib();
  Window::Ptr openWindow(const Window::Desc &);
  Ogre::RenderWindow *createRenderWindow(Window::Ptr, Ogre::Root *);
  InputManager::Ptr createInputManager(Window::Ptr);
}

#endif
