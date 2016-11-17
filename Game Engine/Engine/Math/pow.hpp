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
  
  template <typename T, T VAL, int I>
  struct Pow {
  public:
    static const T VALUE = VAL * Pow<T, VAL, I - 1>::VALUE;
  };
  
  template <typename T, T VAL>
  struct Pow<T, VAL, 1> {
  public:
    static const T VALUE = VAL;
  };
}

#endif
