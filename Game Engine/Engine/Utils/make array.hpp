//
//  make array.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_make_array_hpp
#define engine_utils_make_array_hpp

#include <utility>
#include <array>

namespace Utils {
  template <typename T, size_t ...I, typename ...ARGS>
  std::array<T, sizeof...(I)> makeArrayHelper(std::index_sequence<I...>, ARGS ...args) {
    return {{(static_cast<void>(I), T(args...))...}};
  }

  ///Make a std::array<T, SIZE> by constructing the elements from the arguments given
  template <typename T, size_t SIZE, typename ...ARGS>
  std::array<T, SIZE> makeArray(ARGS ...args) {
    return makeArrayHelper<T>(std::make_index_sequence<SIZE>(), std::forward<ARGS>(args)...);
  }
}

#endif
