//
//  combine.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_combine_hpp
#define engine_utils_combine_hpp

#include <tuple>
#include <functional>
#include "int least.hpp"
#include "variadic type traits.hpp"

namespace Utils {
  template <typename First>
  constexpr uint_fit_t<First> combine(const First first) {
    return static_cast<uint_fit_t<First>>(first);
  }

  template <typename First, typename ...Rest>
  constexpr std::enable_if_t<
    allEither<std::is_integral, std::is_enum, First, Rest...>,
    uint_fit_t<First, Rest...>
  >
  combine(const First first, const Rest... rest) {
    return (
      static_cast<uint_fit_t<First, Rest...>>(first) << (
        (sizeof(Rest) + ...) * 8
      )
    ) | combine(rest...);
  }
  
  //Int cannot be the last template parameter because Rest is a parameter pack.
  //Overloading the function provides a better inferface
  
  #define DECOMPOSE(Int)                                                        \
  template <typename First, typename ...Rest>                                   \
  constexpr std::enable_if_t<                                                   \
    allEither<std::is_integral, std::is_enum, First, Rest...>,                  \
    std::tuple<First, Rest...>                                                  \
  >                                                                             \
  decompose(const Int set) {                                                    \
    return std::tuple_cat(                                                      \
      static_cast<First>(set >> ((sizeof(Rest) + ...) * 8)),                    \
      decompose<Int, Rest...>(set)                                              \
    );                                                                          \
  }
  
  DECOMPOSE(uint8_t)
  DECOMPOSE(uint16_t)
  DECOMPOSE(uint32_t)
  DECOMPOSE(uint64_t)
  
  #undef DECOMPOSE
  
  template <typename Type, typename Tuple, size_t ...Is>
  Type constructFromTuple(Tuple &&tuple, std::index_sequence<Is...>) {
    return {std::get<Is>(std::forward<Tuple>(tuple))...};
  }
  
  template <typename Type, typename Tuple>
  Type constructFromTuple(Tuple &&tuple) {
    return constructFromTuple<Type>(
      std::forward<Tuple>(tuple),
      std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>()
    );
  }

  constexpr uint32_t boolCombine(const bool first) {
    return static_cast<uint32_t>(first);
  }

  template <typename ...Rest>
  constexpr std::enable_if_t<allSameAs<bool, Rest...>, uint32_t>
  boolCombine(const bool first, const Rest... rest) {
    return (static_cast<uint32_t>(first) << sizeof...(Rest)) | boolCombine(rest...);
  }

  //based on boost::hash_combine

  template <typename First>
  size_t hashCombine(First first) {
    const std::hash<First> hasher;
    return hasher(first);
  }

  template <typename First, typename ...Rest>
  size_t hashCombine(First first, Rest... rest) {
    const std::hash<First> hasher;
    const size_t firstHash = hasher(first);
    return firstHash ^ (hashCombine(rest...) + 0x9e3779b9 + (firstHash << 6) + (firstHash >> 2));
  }
}

#endif
