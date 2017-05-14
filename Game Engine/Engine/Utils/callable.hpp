//
//  callable.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_callable_hpp
#define engine_utils_callable_hpp

//C++17 has std::is_callable but my compiler doesn't support that yet

#include <utility>

template <typename...>
using void_t = void;

template <typename T, typename ...ARGS>
struct is_callable {
private:
  using yes = char(&)[1];
  using no = char(&)[2];
  
  template <typename FUNC>
  static yes test(void_t<decltype(std::declval<FUNC>()(std::declval<ARGS>()...))> *);
  
  template <typename>
  static no test(...);

public:
  static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
};

template <typename T, typename ...ARGS>
constexpr bool is_callable_v = is_callable<T, ARGS...>::value;

#endif
