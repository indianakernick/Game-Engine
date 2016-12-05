//
//  sdl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl.hpp"

#ifdef _SDL_events_h

void Input::Managers::SDL::enableRelativeMouse() {
  SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Input::Managers::SDL::disableRelativeMouse() {
  SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool Input::Managers::SDL::isRelativeMouseEnabled() {
  return SDL_GetRelativeMouseMode();
}

void Input::Managers::SDL::update(DeltaType) {
  bool relativeMouseMode = SDL_GetRelativeMouseMode();

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        quit();
        break;
      
      case SDL_MOUSEMOTION:
        if (relativeMouseMode) {
          mouseMovedRel({event.motion.xrel, event.motion.yrel});
        } else {
          mouseMovedAbs({event.motion.x, event.motion.y});
        }
        break;
      
      case SDL_MOUSEWHEEL:
        mouseScroll({event.wheel.x, event.wheel.y});
        break;
      
      case SDL_MOUSEBUTTONDOWN:
        mouseDown(fromIndex(event.button.button));
        break;
      case SDL_MOUSEBUTTONUP:
        mouseUp(fromIndex(event.button.button));
        break;
      
      case SDL_KEYDOWN:
        if (!event.key.repeat) {
          keyDown(fromScancode(event.key.keysym.scancode));
        }
        break;
      case SDL_KEYUP:
        keyUp(fromScancode(event.key.keysym.scancode));
        break;
    }
  }
}

Input::Key::Type Input::Managers::SDL::fromScancode(int scancode) {
  using namespace Key;
  if (scancode >= SDL_SCANCODE_A && scancode <= SDL_SCANCODE_Z) {
    return scancode - SDL_SCANCODE_A + A;
  } else if (scancode >= SDL_SCANCODE_0 && scancode <= SDL_SCANCODE_9) {
    return scancode - SDL_SCANCODE_0 + NUM_0;
  } else if (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
    return scancode - SDL_SCANCODE_F1 + F1;
  } else if (scancode >= SDL_SCANCODE_RETURN && scancode <= SDL_SCANCODE_BACKSLASH) {
    static const Key::Type KEYS[] = {
      ENTER,
      ESCAPE,
      BACKSPACE,
      TAB,
      SPACE,
      MINUS,
      EQUAL,
      LEFT_BRACKET,
      RIGHT_BRACKET,
      BACK_SLASH,
    };
    return KEYS[scancode - SDL_SCANCODE_RETURN];
  } else if (scancode >= SDL_SCANCODE_SEMICOLON && scancode <= SDL_SCANCODE_CAPSLOCK) {
    static const Key::Type KEYS[] = {
      SEMICOLON,
      QUOTE,
      BACK_QUOTE,
      COMMA,
      DOT,
      SLASH,
      CAPS_LOCK
    };
    return KEYS[scancode - SDL_SCANCODE_SEMICOLON];
  } else if (scancode >= SDL_SCANCODE_LCTRL && scancode <= SDL_SCANCODE_RGUI) {
    static const Key::Type KEYS[] = {
      CONTROL,
      SHIFT,
      ALT,
      LEFT_META,
      CONTROL,
      SHIFT,
      ALT,
      RIGHT_META
    };
    return KEYS[scancode - SDL_SCANCODE_LCTRL];
  } else if (scancode >= SDL_SCANCODE_RIGHT && scancode <= SDL_SCANCODE_UP) {
    static const Key::Type KEYS[] = {
      RIGHT,
      LEFT,
      DOWN,
      UP
    };
    return KEYS[scancode - SDL_SCANCODE_RIGHT];
  }
  
  return UNKNOWN;
}

Input::MButton::Type Input::Managers::SDL::fromIndex(uint8_t mButtonIndex) {
  if (mButtonIndex > 3) {
    return MButton::UNKNOWN;
  } else {
    return mButtonIndex;
  }
}

#endif
