//
//  type name.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_type_name_hpp
#define engine_utils_type_name_hpp

#include <string>

///Demangles the name returned by std::type_info::name()
std::string demangle(const char *);

///Get the formatted name for the type of a value
template <typename T>
std::string valueTypeName(T &&v) {
  return demangle(typeid(std::forward<T>(v)).name());
}

template <typename First, typename... Rest>
std::string valueTypeName(First &&first, Rest &&... rest) {
  return valueTypeName(std::forward<First>(first)) + ", " +
         valueTypeName(std::forward<Rest>(rest)...);
}

///Get the formatted name for a type
template <typename T>
std::string typeName() {
  return demangle(typeid(T).name());
}

template <typename... Rest>
std::enable_if_t<sizeof...(Rest) == 0, std::string>
variadicTypeName() {
  return "";
}

template <typename First>
std::string variadicTypeName() {
  return typeName<First>();
}

template <typename First, typename... Rest>
std::enable_if_t<(sizeof...(Rest) > 0), std::string>
variadicTypeName() {
  return variadicTypeName<First>() + ", " + variadicTypeName<Rest...>();
}

#endif
