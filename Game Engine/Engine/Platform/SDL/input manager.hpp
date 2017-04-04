//
//  input manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 3/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_sdl_input_manager_hpp
#define engine_platform_sdl_input_manager_hpp

#ifdef USE_SDL

#include "../Interface/input manager.hpp"
#include <SDL2/SDL.h>

namespace Platform {
  class InputManagerImpl final : public InputManager {
  public:
    InputManagerImpl(glm::ivec2);
  private:
    static Input::Key::Type fromScancode(int);
    static Input::MButton::Type fromIndex(uint8_t);
    
    void sendEvents() override;
    void sendMouseDown(const SDL_Event &);
    void sendMouseUp(const SDL_Event &);
    void sendMouseMove(const SDL_Event &);
    void sendScroll(const SDL_Event &);
    void sendKeyDown(const SDL_Event &);
    void sendKeyUp(const SDL_Event &);
    void sendWindow(const SDL_Event &);
    void sendQuit(const SDL_Event &);
  };
}

#endif

#endif
