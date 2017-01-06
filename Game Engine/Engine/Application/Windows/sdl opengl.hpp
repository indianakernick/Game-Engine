//
//  sdl opengl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_windows_sdl_opengl_hpp
#define engine_application_windows_sdl_opengl_hpp

#if defined(USE_SDL) && defined(USE_OPENGL)

#include "../window.hpp"
#include "../Renderers/sdl opengl.hpp"
#include "../../Input/Managers/sdl.hpp"

namespace Windows {
  class SDLOpenGL : public Window {
  friend class Renderers::SDLOpenGL;
  public:
    SDLOpenGL() = default;
  
    void open(const Desc &) override;
    Renderer::Ptr createRenderer(const Renderer::Desc &) override;
    Input::Manager::Ptr createInputManager() override;
    void close() override;
    
    void changeTitle(std::string title) override;
    void resize(Geometry::Size) override;
    
    void relMouse(bool) override;
    bool relMouse() override;
    
    void captureMouse(bool) override;
    bool captureMouse() override;
    
    void fullscreen(bool) override;
    bool fullscreen() override;
  
  private:
    SDL_Window *window = nullptr;
    bool mouseCaptured = false;
    bool fullscreenEnabled = false;
  };
}

#endif

#endif
