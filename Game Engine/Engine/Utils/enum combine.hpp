//
//  enum combine.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_enum_combine_hpp
#define engine_utils_enum_combine_hpp

#include "type least bytes.hpp"

template <typename ...ARGS>
constexpr size_t size() {
  return (sizeof(ARGS) + ...);
}

template <typename ...ARGS>
using Ret = uint_least_t<size<ARGS...>()>;

template <typename TYPE>
struct RetSingle {
  using type = std::conditional_t<std::is_integral<TYPE>::value ||
                                  std::is_enum<TYPE>::value,
                                  std::make_unsigned_t<TYPE>,
                                  uint_least_t<sizeof(TYPE)>>;
};

//bool is_integral but cannot be made unsigned
template <>
struct RetSingle<bool> {
  using type = uint8_t;
};

template <typename FIRST>
constexpr typename RetSingle<FIRST>::type combine(FIRST first) {
  return static_cast<typename RetSingle<FIRST>::type>(first);
}

template <typename FIRST, typename... REST>
constexpr Ret<FIRST, REST...> combine(FIRST first, REST... rest) {
  return (static_cast<Ret<FIRST, REST...>>(first) << (size<REST...>() * 8)) | combine(rest...);
}

constexpr uint32_t combineBool(bool first) {
  return static_cast<uint32_t>(first);
}

template <typename ...REST>
constexpr std::enable_if_t<(std::is_same<bool, REST>::value && ...), uint32_t>
combineBool(bool first, REST... rest) {
  return (static_cast<uint32_t>(first) << sizeof...(REST)) | combineBool(rest...);
}

#endif
