//
//  member function.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_member_function_hpp
#define engine_utils_member_function_hpp

///Create a std::function from a const member function pointer
template <typename Class, typename Return, typename ...Args>
auto memFun(
  const Class * const that,
  Return (Class::* const fun)(Args...) const
) {
  return [that, fun] (auto &&... args) -> Return {
    return (that->*fun)(std::forward<decltype(args)>(args)...);
  };
}

///Create a std::function from a member function pointer
template <typename Class, typename Return, typename ...Args>
auto memFun(
  Class * const that,
  Return (Class::* const fun)(Args...)
) {
  return [that, fun] (auto &&... args) -> Return {
    return (that->*fun)(std::forward<decltype(args)>(args)...);
  };
}

///Create a std::function from a member variable pointer
template <typename Class, typename Type>
auto memVar(
  const Class * const that,
  Type Class::* const var
) {
  return [that, var] () -> Type {
    return that->*var;
  };
}

#endif
