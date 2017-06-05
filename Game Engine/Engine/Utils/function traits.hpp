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

template <typename Function>
struct function_traits;

template <typename Function>
using function_ret = typename function_traits<Function>::ret;

template <typename Function, size_t I>
using function_arg = typename function_traits<Function>::template arg<I>;

template <typename Function>
constexpr bool is_member_function = function_traits<Function>::is_member;

template <typename Function>
constexpr bool is_const_member_function = function_traits<Function>::is_const_member;

template <typename Function>
constexpr bool is_lvalue_member_function = function_traits<Function>::is_lvalue_member;

template <typename Function>
constexpr bool is_rvalue_member_function = function_traits<Function>::is_rvalue_member;

template <typename Function>
using member_function_class_type = typename function_traits<Function>::class_type;

//function
template <typename Return, typename ...Args>
struct function_traits<Return (Args...)> {
  using ret = Return;
  
  static constexpr size_t arity = sizeof...(Args);
  
  using args = std::tuple<Args...>;
  
  template <size_t I>
  using arg = typename std::tuple_element<I, args>::type;
  
  static constexpr bool is_member = false;
  static constexpr bool is_const_member = false;
  static constexpr bool is_lvalue_member = false;
  static constexpr bool is_rvalue_member = false;
  
  using class_type = void;
};

template <typename Function, typename Class, bool CONST, bool LVALUE, bool RVALUE>
struct function_traits_helper : function_traits<Function> {
  static constexpr bool is_member = true;
  static constexpr bool is_const_member = CONST;
  static constexpr bool is_lvalue_member = LVALUE;
  static constexpr bool is_rvalue_member = RVALUE;
  
  using class_type = Class;
};

//pointer to function
template <typename Return, typename ...Args>
struct function_traits<Return (*)(Args...)> :
  function_traits<Return (Args...)> {};

//pointer to member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...)> :
  function_traits_helper<Return (Args...), Class, false, false, false> {};

//pointer to const member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...) const> :
  function_traits_helper<Return (Args...), Class, true, false, false> {};

//pointer to lvalue member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...) &> :
  function_traits_helper<Return (Args...), Class, false, true, false> {};

//pointer to const lvalue member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...) const &> :
  function_traits_helper<Return (Args...), Class, true, true, false> {};

//pointer to rvalue member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...) &&> :
  function_traits_helper<Return (Args...), Class, false, false, true> {};

//pointer to const rvalue member function
template <typename Class, typename Return, typename ...Args>
struct function_traits<Return (Class::*) (Args...) const &&> :
  function_traits_helper<Return (Args...), Class, true, false, true> {};

//std::function
template <typename Return, typename ...Args>
struct function_traits<std::function<Return (Args...)>> :
  function_traits<Return (Args...)> {};

//functor
template <typename Functor>
struct function_traits :
  //use member function pointer specialization
  function_traits<decltype(&Functor::operator())> {};

//const function
template <typename Function>
struct function_traits<const Function> : function_traits<Function> {};

//lvalue reference to function
template <typename Function>
struct function_traits<Function &> : function_traits<Function> {};

//rvalue reference to function
template <typename Function>
struct function_traits<Function &&> : function_traits<Function> {};

#endif
