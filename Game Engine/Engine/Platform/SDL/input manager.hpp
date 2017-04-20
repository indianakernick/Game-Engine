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
#include "window manager.hpp"
#include <SDL2/SDL.h>
#include "../../Utils/safe down cast.hpp"

namespace Platform {
  class InputManagerImpl final : public InputManager {
  public:
    explicit InputManagerImpl(std::weak_ptr<WindowManager>);
    ~InputManagerImpl() = default;
    
  private:
    bool keyState[Input::Key::NUM_OF_KEYS] = {0};
    bool mouseState[Input::MButton::NUM_OF_BUTTONS] = {0};
    glm::ivec2 mousePos;
  
    static Input::Key::Type fromScancode(int);
    static Input::MButton::Type fromIndex(uint8_t);
    
    void sendEvents() override;
    void sendMouseDown(const SDL_MouseButtonEvent &, WindowManagerImpl::Ptr);
    void sendMouseUp(const SDL_MouseButtonEvent &, WindowManagerImpl::Ptr);
    void sendMouseMove(const SDL_MouseMotionEvent &, WindowManagerImpl::Ptr);
    void sendScroll(const SDL_MouseWheelEvent &, WindowManagerImpl::Ptr);
    void sendKeyDown(const SDL_KeyboardEvent &, WindowManagerImpl::Ptr);
    void sendKeyUp(const SDL_KeyboardEvent &, WindowManagerImpl::Ptr);
    void sendWindowEvent(const SDL_WindowEvent &, WindowManagerImpl::Ptr);
    void sendQuit(WindowManagerImpl::Ptr);
  };
}

#endif

#endif
