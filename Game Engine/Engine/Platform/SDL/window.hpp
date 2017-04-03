//
//  window.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_sdl_opengl_window_hpp
#define engine_platform_sdl_opengl_window_hpp

#ifdef USE_SDL

#include "../Interface/window.hpp"
#include <SDL2/SDL.h>
#include "../../Utils/bool enable.hpp"

namespace Platform {
  class WindowImpl : public Window {
  public:
    WindowImpl(SDL_Window *, bool, bool);
    ~WindowImpl();
    
    void title(const std::string &) override final;
    std::string title() const override final;
    
    void size(Geometry::Size) override final;
    Geometry::Size size() const override final;
    
    void relMouse(bool) override final;
    bool relMouse() const override final;
    
    void captureMouse(bool) override final;
    bool captureMouse() const override final;
    
    void fullscreen(bool) override final;
    bool fullscreen() const override final;
    
    SDL_Window *getWindow() const;
  private:
    SDL_Window *window;
    bool mouseCaptured;
    bool fullscreenEnabled;
  };
}

#endif

#endif
