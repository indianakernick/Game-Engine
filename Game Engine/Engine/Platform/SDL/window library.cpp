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
  if (SDL_Init(SDL_INIT_EVENTS) == 0) {
    LOG_INFO(PLATFORM, "SDL initialized successfully");
  } else {
    LOG_ERROR(PLATFORM, "SDL failed to initialize: %s", SDL_GetError());
  }
}

void Platform::quitLib() {
  SDL_Quit();
}

Ogre::RenderWindow *Platform::createRenderWindow(std::weak_ptr<Window> window, Ogre::Root *root) {
  if (window.expired()) {
    LOG_ERROR(PLATFORM, "Tried to from Ogre::RenderWindow from window that was closed");
    return nullptr;
  }
  std::shared_ptr<Window> strongWindow = window.lock();
  
  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_Window *sdlWindow = Utils::safeDownCast<WindowImpl>(strongWindow)->getWindow();
  if (!SDL_GetWindowWMInfo(sdlWindow, &wmInfo)) {
    LOG_ERROR(PLATFORM, "Could not get WMInfo: %s", SDL_GetError());
  }
  
  Ogre::NameValuePairList params;
  
  //i don't even know if this will work on all these platforms
  //i shouldn't have to write code like this. Ogre should just use SDL as
  //it's windowing system. It would save a lot of a people a lot of hassle
  
  #if defined(SDL_VIDEO_DRIVER_WINDOWS)
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    wmInfo.win.window
  );
  #elif defined(SDL_VIDEO_DRIVER_WINRT)
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    wmInfo.winrt.window
  );
  #elif defined(SDL_VIDEO_DRIVER_X11)
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    wmInfo.x11.window
  );
  #elif defined(SDL_VIDEO_DRIVER_DIRECTFB)
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    wmInfo.dfb.window
  );
  #elif defined(SDL_VIDEO_DRIVER_COCOA)
  params["macAPI"] = "cocoa";
  params["macAPICocoaUseNSView"] = "true";
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    getNSView(wmInfo.info.cocoa.window)
  );
  #elif defined(SDL_VIDEO_DRIVER_UIKIT)
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    wmInfo.uikit.window
  );
  #elif defined(SDL_VIDEO_DRIVER_ANDROID)
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    wmInfo.android.window
  );
  //skipped Wayland and Mir
  #elif defined(SDL_VIDEO_DRIVER_VIVANTE)
  params["externalWindowHandle"] = Ogre::StringConverter::toString(
    wmInfo.dfb.window
  );
  #endif
  
  const glm::ivec2 size = strongWindow->size();
  return root->createRenderWindow("Game Engine", size.x, size.y, false, &params);
}

Platform::WindowManager::Ptr Platform::createWindowManager() {
  return std::make_shared<WindowManagerImpl>();
}

Platform::InputManager::Ptr Platform::createInputManager(WindowManager::Ptr windowManager) {
  return std::make_shared<InputManagerImpl>(windowManager);
}

#endif
