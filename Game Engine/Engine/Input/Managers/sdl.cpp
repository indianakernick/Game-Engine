//
//  sdl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "sdl.hpp"

#ifdef _SDL_events_h

Input::Managers::SDL::SDL(Geometry::Size windowSize)
  : Manager(windowSize) {}

void Input::Managers::SDL::sendEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEBUTTONDOWN: {
        Log::writeNow(Log::INPUT, Log::INFO, "Mouse button down");
        
        MButton::Type button = fromIndex(event.button.which);
        mouseState[button] = true;
      
        MouseDown::Ptr mouseDown = std::make_shared<MouseDown>();
        mouseDown->pos = {event.button.x, event.button.y};
        mouseDown->button = button;
        mouseDown->repeat = event.button.clicks;
        sendEvent(mouseDown);
        break;
      }
      
      case SDL_MOUSEBUTTONUP: {
        Log::writeNow(Log::INPUT, Log::INFO, "Mouse button up");
        
        MButton::Type button = fromIndex(event.button.which);
        mouseState[button] = false;
      
        MouseUp::Ptr mouseUp = std::make_shared<MouseUp>();
        mouseUp->pos = {event.button.x, event.button.y};
        mouseUp->button = button;
        sendEvent(mouseUp);
        break;
      }
      
      case SDL_MOUSEMOTION: {
        Log::writeNow(Log::INPUT, Log::INFO, "Mouse motion");
        
        mousePos = {event.motion.x, event.motion.y};
      
        MouseMove::Ptr mouseMove = std::make_shared<MouseMove>();
        mouseMove->pos = mousePos;
        mouseMove->delta = {event.motion.xrel, event.motion.yrel};
        sendEvent(mouseMove);
        break;
      }
      
      case SDL_MOUSEWHEEL: {
        Log::writeNow(Log::INPUT, Log::INFO, "Mouse wheel");
        
        Scroll::Ptr scroll = std::make_shared<Scroll>();
        scroll->pos = mousePos;
        scroll->delta = {event.wheel.x, event.wheel.y};
        sendEvent(scroll);
        break;
      }
      
      case SDL_KEYDOWN: {
        Log::writeNow(Log::INPUT, Log::INFO, "Key down");
        
        Key::Type key = fromScancode(event.key.keysym.scancode);
        keyState[key] = true;
        Mod::Type mod = getModifiers(keyState);
        
        KeyDown::Ptr keyDown = std::make_shared<KeyDown>();
        keyDown->key = key;
        keyDown->modifiers = mod;
        keyDown->character = codeToChar(key, mod);
        keyDown->repeat = event.key.repeat;
        sendEvent(keyDown);
        break;
      }
      
      case SDL_KEYUP: {
        Log::writeNow(Log::INPUT, Log::INFO, "Key up");
        
        Key::Type key = fromScancode(event.key.keysym.scancode);
        keyState[key] = true;
        
        KeyUp::Ptr keyUp = std::make_shared<KeyUp>();
        keyUp->key = key;
        sendEvent(keyUp);
        break;
      }
      
      case SDL_WINDOWEVENT: {
        Log::writeNow(Log::INPUT, Log::INFO, "Window event");
        
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
          WindowResize::Ptr windowResize = std::make_shared<WindowResize>();
          windowResize->prevSize = windowSize;
          windowSize = {event.window.data1, event.window.data2};
          windowResize->size = windowSize;
          sendEvent(windowResize);
        }
        break;
      }
      
      case SDL_QUIT:
        Log::writeNow(Log::INPUT, Log::INFO, "Quit");
        
        quitEvent(std::make_shared<Quit>());
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
