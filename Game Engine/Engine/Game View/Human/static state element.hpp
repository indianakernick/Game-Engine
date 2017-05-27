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
  
    static_assert(NUM_SUB_STATES != 0);
  
  public:
    explicit StaticStateElement(const std::string &id, SubState initSubState = 0)
      : StateElement(id, NUM_SUB_STATES, initSubState) {}
  };
  
  template <>
  class StaticStateElement<1> : public StateElement {
  public:
    explicit StaticStateElement(const std::string &id)
      : StateElement(id, 1, 0) {}
  };
}

#endif
