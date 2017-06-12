//
//  combine.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_combine_hpp
#define engine_utils_combine_hpp

#include "int least.hpp"
#include <functional>
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
