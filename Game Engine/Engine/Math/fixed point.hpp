//
//  fixed point.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_fixed_point_hpp
#define engine_math_fixed_point_hpp

#include "../Utils/int least.hpp"
#include <type_traits>
#include <cmath>
#include <iostream>
#include "round.hpp"

//i just read a proposal for fixed point data types in the standard library
//http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3352.html
//It's pretty much what my implementation will be if I complete it. But
//i don't need fixed point arithmetic. By the time I do need it, fixed point
//might be in the std library

namespace Math {
  template <size_t INTEGRAL, size_t FRACTION>
  class FixedPoint {
  
    static_assert(0 < INTEGRAL && INTEGRAL <= 64, "Integral size out of range");
    static_assert(0 < FRACTION && FRACTION <= 64, "Fraction size out of range");
  
    template <size_t INT, size_t FRAC>
    friend class FixedPoint;
  
  private:
    static constexpr size_t SIZE = Math::divCeil(INTEGRAL + FRACTION, 8);
    using DataType = uint_least_t<SIZE>;
    using IntType = uint_least_t<Math::divCeil(INTEGRAL, 8)>;
    using FracType = uint_least_t<Math::divCeil(FRACTION, 8)>;
    static constexpr DataType ONE = 1;
    static constexpr DataType INT_MASK = ((ONE << INTEGRAL) - 1) << FRACTION;
    static constexpr DataType FRAC_MASK = (ONE << FRACTION) - 1;
    
  public:
    FixedPoint(const FixedPoint &) = default;
    FixedPoint(FixedPoint &&) = default;
    FixedPoint &operator=(const FixedPoint &) = default;
    FixedPoint &operator=(FixedPoint &&) = default;
    
    FixedPoint()
      : data(0) {}
    
    template <typename T>
    explicit FixedPoint(const T num)
      : data(from(num)) {
    }
    
    template <size_t OLD_INT, size_t OLD_FRAC>
    explicit FixedPoint(const FixedPoint<OLD_INT, OLD_FRAC> other)
      : data(from(other)) {}
    
    template <typename T>
    T as() const {
      return to<T>(data);
    }
    
    template <size_t NEW_INT, size_t NEW_FRAC>
    FixedPoint<NEW_INT, NEW_FRAC> as() const {
      return to<NEW_INT, NEW_FRAC>(data);
    }
    
    inline bool operator==(const FixedPoint other) const {
      return data == other.data;
    }
    inline bool operator!=(const FixedPoint other) const {
      return data != other.data;
    }
    inline bool operator< (const FixedPoint other) const {
      return data < other.data;
    }
    inline bool operator<=(const FixedPoint other) const {
      return data <= other.data;
    }
    inline bool operator> (const FixedPoint other) const {
      return data > other.data;
    }
    inline bool operator>=(const FixedPoint other) const {
      return data >= other.data;
    }
    
    inline FixedPoint &operator+=(const FixedPoint other) {
      data += other.data;
      return *this;
    }
    inline FixedPoint &operator-=(const FixedPoint other) {
      data -= other.data;
      return *this;
    }
    inline FixedPoint &operator*=(const FixedPoint other) {
      data *= other.data;
      data >>= FRACTION;
      return *this;
    }
    inline FixedPoint &operator/=(const FixedPoint other) {
      data /= other.data;
      data <<= FRACTION;
      return *this;
    }
    
    inline FixedPoint operator+(const FixedPoint other) const {
      return {data + other.data};
    }
    inline FixedPoint operator-(const FixedPoint other) const {
      return {data - other.data};
    }
    inline FixedPoint operator*(const FixedPoint other) const {
      return {(data * other.data) >> FRACTION};
    }
    inline FixedPoint operator/(const FixedPoint other) const {
      return {(data / other.data) << FRACTION};
    }
    
    inline DataType &getData() {
      return data;
    }
  private:
    DataType data;
    
    explicit FixedPoint(DataType data)
      : data(data) {}
    
    #define IS_FLOAT std::enable_if_t<std::is_floating_point<T>::value, int> = 0
    #define IS_INT std::enable_if_t<std::is_integral<T>::value, int> = 0
    
    template <typename T, IS_FLOAT>
    DataType from(const T num) const {
      const DataType integral = std::floor(num);
      const DataType fraction = (num - integral) * (ONE << FRACTION);
      return (integral << FRACTION) | fraction;
    }
    
    template <typename T, IS_INT>
    DataType from(const T num) const {
      return static_cast<DataType>(num) << FRACTION;
    }
    
    template <size_t OLD_INT, size_t OLD_FRAC>
    DataType from(const FixedPoint<OLD_INT, OLD_FRAC> other) {
      if (OLD_FRAC > FRACTION) {
        return {static_cast<DataType>(other.data >> (OLD_FRAC - FRACTION))};
      } else {
        return {static_cast<DataType>(other.data) << (FRACTION - OLD_FRAC)};
      }
    }
    
    template <typename T, IS_FLOAT>
    T to(const DataType data) const {
      return static_cast<T>((data & INT_MASK) >> FRACTION) +
             static_cast<T>(data & FRAC_MASK) / (ONE << FRACTION);
    }
    
    template <typename T, IS_INT>
    T to(const DataType data) const {
      return (data & INT_MASK) >> FRACTION;
    }
    
    template <size_t NEW_INT, size_t NEW_FRAC>
    FixedPoint<NEW_INT, NEW_FRAC> to(const DataType data) const {
      using RetDataType = typename FixedPoint<NEW_INT, NEW_FRAC>::DataType;
      if (FRACTION > NEW_FRAC) {
        return {static_cast<RetDataType>(data >> (FRACTION - NEW_FRAC))};
      } else {
        return {static_cast<RetDataType>(data) << (NEW_FRAC - FRACTION)};
      }
    }
    
    #undef IS_FLOAT
    #undef IS_INT
  };
};

#endif
