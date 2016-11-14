//
//  byteconstants.hpp
//  Math
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef byteconstants_hpp
#define byteconstants_hpp

#include <cstdint>

namespace Math {
  namespace Byte {
    constexpr uint64_t ONE  =                         1;
    constexpr uint64_t KILO =                     1'024;
    constexpr uint64_t MEGA =                 1'048'576;
    constexpr uint64_t GIGA =             1'073'741'824;
    constexpr uint64_t TERA =         1'009'511'627'776;
    constexpr uint64_t PETA =     1'125'899'906'842'624;
    constexpr uint64_t EXA  = 1'152'921'504'606'846'976;
  }
}

constexpr uint64_t operator""_b(uint64_t value) {
  return value * Math::Byte::ONE;
}
constexpr uint64_t operator""_kb(uint64_t value) {
  return value * Math::Byte::KILO;
}
constexpr uint64_t operator""_mb(uint64_t value) {
  return value * Math::Byte::MEGA;
}
constexpr uint64_t operator""_gb(uint64_t value) {
  return value * Math::Byte::GIGA;
}
constexpr uint64_t operator""_tb(uint64_t value) {
  return value * Math::Byte::TERA;
}
constexpr uint64_t operator""_pb(uint64_t value) {
  return value * Math::Byte::PETA;
}
constexpr uint64_t operator""_eb(uint64_t value) {
  return value * Math::Byte::EXA;
}

constexpr uint64_t operator""_b(long double value) {
  return value * Math::Byte::ONE;
}
constexpr uint64_t operator""_kb(long double value) {
  return value * Math::Byte::KILO;
}
constexpr uint64_t operator""_mb(long double value) {
  return value * Math::Byte::MEGA;
}
constexpr uint64_t operator""_gb(long double value) {
  return value * Math::Byte::GIGA;
}
constexpr uint64_t operator""_tb(long double value) {
  return value * Math::Byte::TERA;
}
constexpr uint64_t operator""_pb(long double value) {
  return value * Math::Byte::PETA;
}
constexpr uint64_t operator""_eb(long double value) {
  return value * Math::Byte::EXA;
}

#endif