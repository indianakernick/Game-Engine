//
//  member function.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_member_function_hpp
#define engine_utils_member_function_hpp

#include <functional>

///Create a std::function from a const member function pointer
template <typename T, typename RET, typename ...ARGS>
std::function<RET (ARGS...)> memFun(const T *that, RET (T::*fun)(ARGS...) const) {
  return [that, fun] (ARGS... args) -> RET {
    return (that->*fun)(std::forward<ARGS>(args)...);
  };
}

///Create a std::function from a member function pointer
template <typename T, typename RET, typename ...ARGS>
std::function<RET (ARGS...)> memFun(T *that, RET (T::*fun)(ARGS...)) {
  return [that, fun] (ARGS... args) -> RET {
    return (that->*fun)(std::forward<ARGS>(args)...);
  };
}

///Create a std::function from a member variable pointer
template <typename T, typename RET>
std::function<RET ()> memVar(const T *that, RET T::*var) {
  return [that, var] () -> RET {
    return that->*var;
  };
}

#endif
