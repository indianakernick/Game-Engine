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

#define MUST_BE_INTEGRAL(RET) typename std::enable_if<std::is_integral<T>::value, RET>::type

namespace Memory {
  namespace Bit {
    template <typename T>
    constexpr MUST_BE_INTEGRAL(T) toMask(uint8_t i) {
      return (static_cast<T>(1) << i);
    }
    template <typename T>
    inline MUST_BE_INTEGRAL(T) flip(T num, uint8_t i) {
      assert(i < 64);
      return num ^ toMask<T>(i);
    }
    template <typename T>
    inline MUST_BE_INTEGRAL(T) on(T num, uint8_t i) {
      assert(i < 64);
      return num | toMask<T>(i);
    }
    template <typename T>
    inline MUST_BE_INTEGRAL(T) off(T num, uint8_t i) {
      assert(i < 64);
      return num & ~toMask<T>(i);
    }
    template <typename T>
    inline MUST_BE_INTEGRAL(T) set(T num, uint8_t i, bool value) {
      assert(i < 64);
      return value ? num | toMask<T>(i) : num & ~toMask<T>(i);
    }
    template <typename T>
    inline MUST_BE_INTEGRAL(bool) get(T num, uint8_t i) {
      assert(i < 64);
      return num & toMask<T>(i);
    }
  }
}

#endif
