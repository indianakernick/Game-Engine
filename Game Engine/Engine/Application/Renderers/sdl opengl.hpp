//
//  sdl opengl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_renderers_sdl_opengl_hpp
#define engine_application_renderers_sdl_opengl_hpp

#if defined(USE_SDL) && defined(USE_OPENGL)

#include "opengl.hpp"
#include "../renderer.hpp"
#include "../../Utils/logger.hpp"
#include "../../Utils/profiler.hpp"

namespace Renderers {
  class SDLOpenGL : public Renderer {
  public:
    SDLOpenGL() = default;
    
    void init(Window *window, const Desc &) override;
    void quit() override;
    
    void preRender() override;
    void postRender() override;
  private:
    SDL_GLContext context;
    SDL_Window *window;
    glm::vec4 clearColor;
  };
}

#include "../Windows/sdl opengl.hpp"

#endif

#endif
