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
  template <typename T, size_t ...I, typename ...Args>
  std::array<T, sizeof...(I)> makeArrayHelper(std::index_sequence<I...>, Args... args) {
    return {{(void(I), T(args...))...}};
  }

  ///Make a std::array<Type, SIZE> by constructing the elements from the arguments given
  template <typename Type, size_t SIZE, typename ...Args>
  std::array<T, SIZE> makeArray(Args... args) {
    return makeArrayHelper<T>(
      std::make_index_sequence<SIZE>(),
      args...
    );
  }
}

#endif
