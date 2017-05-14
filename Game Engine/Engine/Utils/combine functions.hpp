//
//  combine functions.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_combine_functions_hpp
#define engine_utils_combine_functions_hpp

#include "callable.hpp"
#include "move test.hpp"

template <typename LEFT, typename RIGHT>
struct combine_functions : public MoveTest<combine_functions<LEFT, RIGHT>> {
  combine_functions(const LEFT &left, const RIGHT &right)
   : left(left), right(right) {}
  
  template <typename ...ARGS>
  std::enable_if_t<
  //i cant quite get this to work
    true
    //is_callable_v<LEFT, std::decay_t<ARGS>...> &&
    //is_callable_v<RIGHT, std::decay_t<ARGS>...>
  > operator()(ARGS... args) const {
    left(args...);
    right(args...);
  }
  
private:
  mutable LEFT left;
  mutable RIGHT right;
};

template <typename LEFT, typename RIGHT>
combine_functions<
  std::decay_t<LEFT>,
  std::decay_t<RIGHT>
>
operator+(
  const LEFT &left,
  const RIGHT &right
) {
  return {left, right};
}

#endif
