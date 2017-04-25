//
//  math.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef math_hpp
#define math_hpp

#include <type_traits>

inline unsigned int ceilToPowerOf2(unsigned int num) {
  return (1 << (sizeof(int) * 8 - __builtin_clz(num - 1))) - (num == 1);
}

inline unsigned long ceilToPowerOf2(unsigned long num) {
  return (1 << (sizeof(long) * 8 - __builtin_clzl(num - 1))) - (num == 1);
}

inline unsigned long long ceilToPowerOf2(unsigned long long num) {
  return (1 << (sizeof(long long) * 8 - __builtin_clzll(num - 1))) - (num == 1);
}

template <typename NUM, typename DEN>
std::common_type_t<NUM, DEN> divRound(NUM num, DEN den) {
  return (num < 0) ^ (den < 0) ? (num - den / 2) / den
                               : (num + den / 2) / den;
}

#endif
