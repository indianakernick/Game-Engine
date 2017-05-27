//
//  button.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_button_hpp
#define engine_game_view_human_button_hpp

#include "static state element.hpp"

namespace UI {
  //should this be a type alias?

  class Button final : public StaticStateElement<1> {
  public:
    using Ptr = std::shared_ptr<Button>;
    
    explicit Button(const std::string &id);
  };
}

#endif
