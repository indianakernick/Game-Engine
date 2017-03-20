//
//  logic.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_logic_hpp
#define engine_math_logic_hpp

#include "../Utils/variadic type traits.hpp"

namespace Math {
  template <typename ...ARGS>
  constexpr std::enable_if_t<allSameAs<bool, ARGS...>, bool>
  all(const ARGS ...args) {
    return (args && ...);
  }
  
  template <typename ...ARGS>
  constexpr std::enable_if_t<allSameAs<bool, ARGS...>, bool>
  any(const ARGS ...args) {
    return (args || ...);
  }
  
  template <typename ...ARGS>
  constexpr std::enable_if_t<allSameAs<bool, ARGS...>, bool>
  none(const ARGS ...args) {
    return (!args && ...);
  }
  
  template <typename ...ARGS>
  constexpr std::enable_if_t<allSameAs<bool, ARGS...>, bool>
  one(const ARGS ...args) {
    return (args + ...) == 1;
  }
}

#endif
