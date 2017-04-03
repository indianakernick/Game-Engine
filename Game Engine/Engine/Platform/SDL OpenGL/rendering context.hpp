//
//  rendering context.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_context_hpp
#define rendering_context_hpp

#ifdef USE_SDL_OPENGL

#include "../Interface/rendering context.hpp"
#include "opengl.hpp"

namespace Platform {
  class RenderingContextImpl final : public RenderingContext {
  public:
    RenderingContextImpl(SDL_Window *, SDL_GLContext);
    ~RenderingContextImpl();
    
    void preRender() override;
    void postRender() override;
  
  private:
    SDL_Window *window;
    SDL_GLContext context;
  };
}

#endif

#endif
