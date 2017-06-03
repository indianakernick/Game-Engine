//
//  draggable.hpp
//  Game Engine
//
//  Created by Indi Kernick on 28/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_draggable_hpp
#define engine_game_view_human_draggable_hpp

#include "static state element.hpp"

namespace UI {
  class Draggable final : public StaticStateElement<1> {
  public:
    using Ptr = std::shared_ptr<Draggable>;
    
    explicit Draggable(const std::string &);
    ~Draggable() = default;
  
  private:
    void onMouseMove(Event::Ptr);
  };
}

#endif
