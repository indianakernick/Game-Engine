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
  
  template<typename T, int I>
  constexpr T pow(T n) {
    T out = 1;
    int i = I;
    const bool neg = I < 0 && (i = -i);
    while (i--) out *= n;
    return neg ? 1 / out : out;
  }
  ///Forces pow to be executed at compile time
  template <typename T, T VAL, int I>
  struct Pow {
  public:
    static const T VALUE = Math::pow<I, T>(VAL);
  };
}

#endif