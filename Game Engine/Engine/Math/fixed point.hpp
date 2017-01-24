//
//  fixed point.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_fixed_point_hpp
#define engine_math_fixed_point_hpp

#include "type least bytes.hpp"
#include <type_traits>
#include <cmath>
#include <iostream>

namespace Math {
  template <size_t INTEGRAL, size_t FRACTION>
  class FixedPoint {
  
    static_assert(0 < INTEGRAL && INTEGRAL <= 64, "Integral size out of range");
    static_assert(0 < FRACTION && FRACTION <= 64, "Fraction size out of range");
  
  private:
    static const size_t SIZE = (INTEGRAL + FRACTION + 7) / 8;
    using DataType = typename TypeLeastBytes<SIZE>::type;
    using IntType = typename TypeLeastBytes<(INTEGRAL + 7) / 8>::type;
    using FracType = typename TypeLeastBytes<(FRACTION + 7) / 8>::type;
    using SelfType = FixedPoint<INTEGRAL, FRACTION>;
  public:
    FixedPoint()
      : data(0) {}
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value, T>::type * = nullptr>
    FixedPoint(T num) {
      DataType integral = std::floor(num);
      DataType fraction = (num - integral) * (ONE << FRACTION);
      data = ((integral << FRACTION) & INT_MASK) |
             (fraction & FRAC_MASK);
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, T>::type * = nullptr>
    FixedPoint(T num)
      : data(static_cast<DataType>(num) << FRACTION) {}
    
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value, T>::type * = nullptr>
    T as() {
      return static_cast<T>((data & INT_MASK) >> FRACTION) +
             static_cast<T>(data & FRAC_MASK) / (ONE << FRACTION);
    }
    
    template <typename T, typename std::enable_if<std::is_integral<T>::value, T>::type * = nullptr>
    T as() {
      return (data & INT_MASK) >> FRACTION;
    }
    
    inline SelfType &operator+=(SelfType other) {
      data += other.data;
      return *this;
    }
    inline SelfType &operator-=(SelfType other) {
      data -= other.data;
      return *this;
    }
    inline SelfType &operator*=(SelfType other) {
      data *= other.data;
      data >>= FRACTION;
      return *this;
    }
    inline SelfType &operator/=(SelfType other) {
      data /= other.data;
      data <<= FRACTION;
      return *this;
    }
    
    /*SelfType operator+(SelfType) const;
    SelfType operator-(SelfType) const;
    SelfType operator*(SelfType) const;
    SelfType operator/(SelfType) const;*/
    
    inline DataType &getData() {
      return data;
    }
  private:
    DataType data;
    static const DataType ONE = 1;
    static const DataType INT_MASK = ((ONE << INTEGRAL) - 1) << FRACTION;
    static const DataType FRAC_MASK = (ONE << FRACTION) - 1;
  };
};

#endif
