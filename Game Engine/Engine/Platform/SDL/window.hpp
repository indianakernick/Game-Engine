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
  class WindowImpl final : public Window {
  public:
    explicit WindowImpl(SDL_Window *);
    ~WindowImpl();
    
    void title(const std::string &) override;
    std::string title() const override;
    
    void pos(glm::ivec2) override;
    glm::ivec2 pos() const override;
    
    void center() override;
    void center(bool, bool) override;
    
    void size(glm::ivec2) override;
    glm::ivec2 size() const override;
    
    void opacity(float) override;
    float opacity() const override;
    
    void relMouse(bool) override;
    bool relMouse() const override;
    
    void captureMouse(bool) override;
    bool captureMouse() const override;
    
    void raise() override;
    
    SDL_Window *getWindow() const;
  private:
    SDL_Window *window;
    bool mouseCaptured;
  };
}

#endif

#endif
