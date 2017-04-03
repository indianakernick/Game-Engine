//
//  rendering context.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_rendering_context_hpp
#define engine_platform_interface_rendering_context_hpp

#include <memory>
#include <glm/vec4.hpp>

namespace Platform {
  class RenderingContext {
  public:
    using Ptr = std::shared_ptr<RenderingContext>;
    
    struct Desc {
      int colorBits = 32;
      int depthBits = 16;
      int stencilBits = 8;
      glm::vec4 clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    };
    
    RenderingContext() = default;
    RenderingContext(const RenderingContext &) = delete;
    RenderingContext(RenderingContext &&) = default;
    virtual ~RenderingContext() = default;
    
    RenderingContext &operator=(const RenderingContext &) = delete;
    RenderingContext &operator=(RenderingContext &&) = default;
    
    virtual void preRender() = 0;
    virtual void postRender() = 0;
  };
}

#endif
