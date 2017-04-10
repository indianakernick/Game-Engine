//
//  new renderer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_new_renderer_hpp
#define engine_game_view_human_new_renderer_hpp

#include "root.hpp"
#include "../../Platform/Interface/render 2d.hpp"
#include "../../Platform/Interface/graphics library.hpp"
#include "../../Application/global resource cache.hpp"
#include "../../Resource/Handles/texture.hpp"
#include "../../Resource/Handles/shader.hpp"

namespace UI {
  class NewRenderer {
  public:
    NewRenderer() = default;
    ~NewRenderer() = default;
    
    void init();
    void render(const Root::Ptr);
  
  private:
    static const Res::ID VERT_ID;
    static const Res::ID FRAG_ID;
  
    Platform::Render2D::List::Ptr renderList;
    Platform::Render2D::Context::Ptr renderContext;
    
    void packChildren(AABBStack &, HeightStack &, const Element::Children &);
    void packElement(SimpleAABB, Height, const Element::Ptr);
    Platform::Render2D::Bounds packBounds(SimpleAABB);
  };
}

#endif
