//
//  bits.hpp
//  Math
//
//  Created by Indi Kernick on 9/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef bits_hpp
#define bits_hpp

#include <cstdint>
#include <cassert>
#include <type_traits>

namespace Math {
  namespace Bit {
    template <typename T>
    constexpr T toMask(uint8_t i) {
      static_assert(std::is_integral<T>::value, "Bitwise operations can only be performed on integral types");
      return (static_cast<T>(1) << i);
    }
    template <typename T>
    inline T flip(T num, uint8_t i) {
      assert(i < 64);
      return num ^ toMask<T>(i);
    }
    template <typename T>
    inline T on(T num, uint8_t i) {
      assert(i < 64);
      return num | toMask<T>(i);
    }
    template <typename T>
    inline T off(T num, uint8_t i) {
      assert(i < 64);
      return num & ~toMask<T>(i);
    }
    template <typename T>
    inline T set(T num, uint8_t i, bool value) {
      assert(i < 64);
      return value ? num | toMask<T>(i) : num & ~toMask<T>(i);
    }
    template <typename T>
    inline bool get(T num, uint8_t i) {
      assert(i < 64);
      return num & toMask<T>(i);
    }
  }
}

#endif