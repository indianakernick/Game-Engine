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

Platform::Window::Ptr Platform::openWindow(const Window::Desc &desc) {
  const uint32_t resizable = boolEnable(desc.resizable, SDL_WINDOW_RESIZABLE);
  const uint32_t fullscreen = boolEnable(desc.fullscreen, SDL_WINDOW_FULLSCREEN);
  
  SDL_Window *window = SDL_CreateWindow(desc.title.c_str(),
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        desc.size.x, desc.size.y,
                                        SDL_WINDOW_SHOWN |
                                        resizable |
                                        fullscreen);
  
  if (window) {
    LOG_INFO(PLATFORM, "Successfully created window");
  } else {
    LOG_ERROR(PLATFORM, "Failed to create window: %s", SDL_GetError());
  }
  
  LOG_INFO(PLATFORM,
    "Window title: \"%s\", size: %i,%i",
    desc.title.c_str(), desc.size.x, desc.size.y);
  
  return std::make_shared<WindowImpl>(window, desc.fullscreen);
}

Ogre::RenderWindow *Platform::createRenderWindow(Window::Ptr window, Ogre::Root *root) {
  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_Window *sdlWindow = safeDownCast<WindowImpl>(window)->getWindow();
  if (!SDL_GetWindowWMInfo(sdlWindow, &wmInfo)) {
    LOG_ERROR(PLATFORM, "Could not get WMInfo: %s", SDL_GetError());
  }
  
  //This is OS X specific
  
  Ogre::NameValuePairList params;
  params["macAPI"] = "cocoa";
  params["macAPICocoaUseNSView"] = "true";
  
  Ogre::String winHandle = Ogre::StringConverter::toString(getNSView(wmInfo.info.cocoa.window));
  params["externalWindowHandle"] = winHandle;
  const glm::ivec2 size = window->size();
  return root->createRenderWindow("Game Engine", size.x, size.y, window->fullscreen(), &params);
}

Platform::InputManager::Ptr Platform::createInputManager() {
  return std::make_shared<InputManagerImpl>();
}

#endif
