//
//  window manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "window manager.hpp"

using namespace Platform;

std::weak_ptr<Window> WindowManagerImpl::openWindow(const Window::Desc &desc) {
  SDL_Window *windowHandle = SDL_CreateWindow(
    desc.title.c_str(),
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    desc.size.x, desc.size.y,
    SDL_WINDOW_SHOWN |
    Utils::boolEnable(desc.resizable, SDL_WINDOW_RESIZABLE)
  );
  
  if (windowHandle) {
    LOG_INFO(PLATFORM, "Successfully created window");
  } else {
    LOG_ERROR(PLATFORM, "Failed to create window: %s", SDL_GetError());
    return {};
  }
  
  std::shared_ptr<Window> window = std::make_shared<WindowImpl>(windowHandle);
  windows.insert({SDL_GetWindowID(windowHandle), window});
  
  return window;
}

void WindowManagerImpl::closeWindow(std::weak_ptr<Window> window) {
  if (window.expired()) {
    LOG_WARNING(PLATFORM, "Tried to close window that was already closed");
    return;
  }
  std::shared_ptr<Window> strongWindow = window.lock();
  
  for (auto w = windows.cbegin(); w != windows.cend(); w++) {
    if (w->second == strongWindow) {
      windows.erase(w);
      return;
    }
  }
  
  LOG_WARNING(PLATFORM, "Tried to close window that was already closed");
}

void WindowManagerImpl::closeAllWindows() {
  windows.clear();
}

std::weak_ptr<Window> WindowManagerImpl::getWindow(WindowID id) {
  auto iter = windows.find(id);
  assert(iter != windows.end());
  return iter->second;
}

void WindowManagerImpl::closeWindow(WindowID id) {
  auto iter = windows.find(id);
  assert(iter != windows.end());
  windows.erase(iter);
}
