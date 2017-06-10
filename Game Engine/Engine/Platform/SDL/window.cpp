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

WindowImpl::WindowImpl(SDL_Window *window)
  : window(window) {
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

void WindowImpl::pos(glm::ivec2 newPos) {
  SDL_SetWindowPosition(window, newPos.x, newPos.y);
}

glm::ivec2 WindowImpl::pos() const {
  glm::ivec2 pos;
  SDL_GetWindowPosition(window, &pos.x, &pos.y);
  return pos;
}

void WindowImpl::center() {
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void WindowImpl::center(bool x, bool y) {
  SDL_SetWindowPosition(
    window,
    Utils::boolEnable(x, SDL_WINDOWPOS_CENTERED),
    Utils::boolEnable(y, SDL_WINDOWPOS_CENTERED)
  );
}

void WindowImpl::size(glm::ivec2 newSize) {
  SDL_SetWindowSize(window, newSize.x, newSize.y);
}

glm::ivec2 WindowImpl::size() const {
  glm::ivec2 size;
  SDL_GetWindowSize(window, &size.x, &size.y);
  return size;
}

void WindowImpl::opacity(float newOpacity) {
  SDL_SetWindowOpacity(window, newOpacity);
}

float WindowImpl::opacity() const {
  float opacity;
  SDL_GetWindowOpacity(window, &opacity);
  return opacity;
}

void WindowImpl::relMouse(bool status) {
  assert(SDL_GetMouseFocus() == window);
  SDL_SetRelativeMouseMode(static_cast<SDL_bool>(status));
}

bool WindowImpl::relMouse() const {
  return SDL_GetRelativeMouseMode() && SDL_GetMouseFocus() == window;
}

void WindowImpl::captureMouse(bool status) {
  assert(SDL_GetMouseFocus() == window);
  SDL_CaptureMouse(static_cast<SDL_bool>(status));
  mouseCaptured = status;
}

bool WindowImpl::captureMouse() const {
  return mouseCaptured;
}

void WindowImpl::raise() {
  SDL_RaiseWindow(window);
}

SDL_Window *WindowImpl::getWindow() const {
  return window;
}

#endif
