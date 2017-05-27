//
//  static state element.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_static_state_element_hpp
#define engine_game_view_human_static_state_element_hpp

#include "state element.hpp"

namespace UI {
  template <StateElement::SubState NUM_SUB_STATES>
  class StaticStateElement : public StateElement {
  public:
    explicit StaticStateElement(const std::string &id, SubState initSubState = 0)
      : StateElement(id, NUM_SUB_STATES, initSubState) {}
  };
}

#endif
