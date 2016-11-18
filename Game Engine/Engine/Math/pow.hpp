//
//  pow.hpp
//  Math
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef pow_hpp
#define pow_hpp

namespace Math {
  /// n ^ 2
  template<typename T>
  constexpr T square(T n) {
    return n*n;
  }
  /// n ^ 3
  template<typename T>
  constexpr T cube(T n) {
    return n*n*n;
  }
  /// n ^ -2
  template<typename T>
  constexpr T invSquare(T n) {
    return 1/(n*n);
  }
  /// n ^ -3
  template<typename T>
  constexpr T invCube(T n) {
    return 1/(n*n*n);
  }
  
  template <int I>
  struct Pow {
    template <typename T>
    static T calc(T val) {
      return val * Pow<I - 1>::calc(val);
    }
  };

  template <>
  struct Pow<1> {
    template <typename T>
    static T calc(T val) {
      return val;
    }
  };

  template <>
  struct Pow<0> {
    template <typename T>
    static T calc(T) {
      return 1;
    }
  };
}

#endif
