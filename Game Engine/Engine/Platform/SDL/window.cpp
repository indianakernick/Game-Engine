//
//  window.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "window.hpp"

#ifdef USE_SDL

using namespace Platform;

WindowImpl::WindowImpl(SDL_Window *window, bool mouseCaptured, bool fullscreenEnabled)
  : window(window), mouseCaptured(mouseCaptured), fullscreenEnabled(fullscreenEnabled) {
  assert(window);
}

WindowImpl::~WindowImpl() {
  SDL_DestroyWindow(window);
}

void WindowImpl::title(const std::string &newTitle) {
  SDL_SetWindowTitle(window, newTitle.c_str());
}

std::string WindowImpl::title() const {
  return SDL_GetWindowTitle(window);
}

void WindowImpl::size(Geometry::Size newSize) {
  SDL_SetWindowSize(window, newSize.w, newSize.h);
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

Geometry::Size WindowImpl::size() const {
  Geometry::Size size;
  SDL_GetWindowSize(window, &size.w, &size.h);
  return size;
}

void WindowImpl::relMouse(bool status) {
  SDL_SetRelativeMouseMode(static_cast<SDL_bool>(status));
}

bool WindowImpl::relMouse() const {
  return SDL_GetRelativeMouseMode();
}

void WindowImpl::captureMouse(bool status) {
  SDL_CaptureMouse(static_cast<SDL_bool>(status));
  mouseCaptured = status;
}

bool WindowImpl::captureMouse() const {
  return mouseCaptured;
}

void WindowImpl::fullscreen(bool status) {
  SDL_SetWindowFullscreen(window, boolEnable(status, SDL_WINDOW_FULLSCREEN));
  fullscreenEnabled = status;
}

bool WindowImpl::fullscreen() const {
  return fullscreenEnabled;
}

SDL_Window *WindowImpl::getWindow() const {
  return window;
}

#endif
