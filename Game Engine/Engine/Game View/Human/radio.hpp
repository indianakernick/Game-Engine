//
//  radio.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_radio_hpp
#define engine_game_view_human_radio_hpp

#include "static state element.hpp"

namespace UI {
  ///A checkbox that is mutually exclusive with its sibling Radios
  class Radio final : public StaticStateElement<2> {
  public:
    using Ptr = std::shared_ptr<Radio>;
    
    static constexpr StateElement::SubState UNCHECKED_STATE = 0;
    static constexpr StateElement::SubState CHECKED_STATE = 1;
    
    explicit Radio(const std::string &id, bool = false);
    
    bool isChecked() const;
    bool isUnchecked() const;
    void check();
    void uncheck();
  };
}

#endif
