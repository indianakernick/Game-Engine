//
//  renderer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_renderer_hpp
#define engine_game_view_human_renderer_hpp

#include "root.hpp"

namespace UI {
  class Renderer {
  public:
    using Ptr = std::shared_ptr<Renderer>;
  
    Renderer() = default;
    virtual ~Renderer() = default;
    
    virtual void init() = 0;
    virtual void render(const Root::Ptr) = 0;
    virtual void quit() = 0;
  };
}

#endif
