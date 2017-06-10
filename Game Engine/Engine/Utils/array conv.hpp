//
//  array conv.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_array_conv_hpp
#define engine_utils_array_conv_hpp

#include <array>

namespace Utils {
  ///Convert a regular array to a std::array
  template <typename T>
  struct array_to_class {
    using type = T;
  };

  ///Convert a regular array to a std::array
  template <typename T, size_t SIZE>
  struct array_to_class<T[SIZE]> {
    using type = std::array<typename array_to_class<T>::type, SIZE>;
  };

  ///Convert a regular array to a std::array
  template <typename T>
  using array_to_class_t = typename array_to_class<T>::type;

  ///Convert a std::array to a regular array
  template <typename T>
  struct class_to_array {
    using type = T;
  };

  ///Convert a std::array to a regular array
  template <typename T, size_t SIZE>
  struct class_to_array<std::array<T, SIZE>> {
    using type = typename class_to_array<T>::type[SIZE];
  };

  ///Convert a std::array to a regular array
  template <typename T>
  using class_to_array_t = typename class_to_array<T>::type;

  ///Is this type an instantiation of std::array?
  template <typename T>
  struct is_array_class : std::false_type {};

  ///Is this type an instantiation of std::array?
  template <typename T, size_t SIZE>
  struct is_array_class<std::array<T, SIZE>> : std::true_type {};

  ///Is this type an instantiation of std::array?
  template <typename T>
constexpr bool is_array_class_v = is_array_class<T>::value;
}

#endif
