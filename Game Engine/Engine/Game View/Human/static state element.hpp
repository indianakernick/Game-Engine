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
  ///A StateElement with a compile-time number of sub states
  template <StateElement::SubState NUM_SUB_STATES, bool ADD_LISTENERS = true>
  class StaticStateElement : public StateElement {
  
    static_assert(NUM_SUB_STATES != 0);
  
  public:
    explicit StaticStateElement(const std::string &id, SubState initSubState = 0)
      : StateElement(id, ADD_LISTENERS, NUM_SUB_STATES, initSubState) {}
  };
  
  template <bool ADD_LISTENERS>
  class StaticStateElement<1, ADD_LISTENERS> : public StateElement {
  public:
    explicit StaticStateElement(const std::string &id)
      : StateElement(id, ADD_LISTENERS, 1, 0) {}
  };
}

#endif
