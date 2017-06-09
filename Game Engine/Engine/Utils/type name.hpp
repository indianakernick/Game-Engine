//
//  type name.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_type_name_hpp
#define engine_utils_type_name_hpp

#include <experimental/string_view>

///Get the formatted name for a type
template <typename T>
constexpr std::experimental::string_view getTypeName() {
  std::experimental::string_view function = __PRETTY_FUNCTION__;
  function.remove_prefix(function.rfind('['));
  function.remove_prefix(function.find('='));
  function.remove_prefix(2);
  function.remove_suffix(1);
  return function;
}

///Get the formatted name for a list of types
template <typename... Rest>
std::enable_if_t<sizeof...(Rest) == 0, std::string>
getVariadicTypeName() {
  return "";
}

///Get the formatted name for a list of types
template <typename First>
std::string getVariadicTypeName() {
  return getTypeName<First>();
}

///Get the formatted name for a list of types
template <typename First, typename... Rest>
std::enable_if_t<(sizeof...(Rest) > 0), std::string>
getVariadicTypeName() {
  return getVariadicTypeName<First>() + ", " + getVariadicTypeName<Rest...>();
}

#endif
