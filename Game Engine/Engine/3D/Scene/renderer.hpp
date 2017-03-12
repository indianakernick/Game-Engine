//
//  renderer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_renderer_hpp
#define engine_3d_scene_renderer_hpp

#include "root.hpp"
#include "../Program manager.hpp"

namespace Scene {
  class Renderer {
  public:
    using Ptr = std::shared_ptr<Renderer>;
  
    Renderer() = default;
    virtual ~Renderer() = default;
    
    virtual void init(Graphics3D::ProgramManager::Ptr) = 0;
    virtual void render(Root::Ptr) = 0;
    virtual void quit() = 0;
  };
};

#endif
