//
//  function traits.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_function_traits_hpp
#define engine_utils_function_traits_hpp

#include <tuple>
#include <functional>

template <typename Return, typename ...Args>
struct function_traits_helper {
  static constexpr size_t arity = sizeof...(Args);
  using ret = Return;
  
  template <size_t I>
  using arg = typename std::tuple_element<I, std::tuple<Args...>>::type;
};

template <typename Function>
struct function_traits;

template <typename Function>
using function_ret = typename function_traits<Function>::ret;

template <typename Function, size_t I>
using function_arg = typename function_traits<Function>::template arg<I>;

//function
template <typename Return, typename ...Args>
struct function_traits<Return (Args...)> :
  public function_traits_helper<Return, Args...> {};

//pointer to function
template <typename Return, typename ...Args>
struct function_traits<Return (*)(Args...)> :
  public function_traits_helper<Return, Args...> {};

//pointer to member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...)> :
  public function_traits_helper<Return, Args...> {
  static constexpr bool is_const = false;
};

//pointer to const member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...) const> :
  public function_traits_helper<Return, Args...> {
  static constexpr bool is_const = true;
};

//std::function
template <typename Return, typename ...Args>
struct function_traits<std::function<Return (Args...)>> :
  public function_traits_helper<Return, Args...> {};

//functor
template <typename Functor>
struct function_traits :
  //use member function pointer specialization
  public function_traits<decltype(&std::decay_t<Functor>::operator())> {};

#endif
