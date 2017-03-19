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

template <typename FIRST>
constexpr uint_fit_t<FIRST> combine(FIRST first) {
  return static_cast<uint_fit_t<FIRST>>(first);
}

template <typename FIRST, typename ...REST>
constexpr std::enable_if_t<
  allEither<std::is_integral, std::is_enum, FIRST, REST...>,
  uint_fit_t<FIRST, REST...>
>
combine(FIRST first, REST... rest) {
  return (
    static_cast<uint_fit_t<FIRST, REST...>>(first) << (
      (sizeof(REST) + ...) * 8
    )
  ) | combine(rest...);
}

constexpr uint32_t boolCombine(bool first) {
  return static_cast<uint32_t>(first);
}

template <typename ...REST>
constexpr std::enable_if_t<allSameAs<bool, REST...>, uint32_t>
boolCombine(bool first, REST... rest) {
  return (static_cast<uint32_t>(first) << sizeof...(REST)) | boolCombine(rest...);
}

//based on boost::hash_combine

template <typename FIRST>
size_t hashCombine(FIRST first) {
  std::hash<FIRST> hasher;
  return hasher(first);
}

template <typename FIRST, typename ...REST>
size_t hashCombine(FIRST first, REST... rest) {
  std::hash<FIRST> hasher;
  const size_t firstHash = hasher(first);
  return firstHash ^ (hashCombine(rest...) + 0x9e3779b9 + (firstHash << 6) + (firstHash >> 2));
}

#endif
