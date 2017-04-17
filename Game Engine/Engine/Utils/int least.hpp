//
//  int least.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_int_least_hpp
#define engine_utils_int_least_hpp

#include <cstdint>
#include <type_traits>
#include "../Math/round.hpp"

///Returns a signed integral type of at least the number of bytes specified
template <size_t BYTES>
struct int_least {
  using type = typename int_least<Math::ceilToPower(2, BYTES)>::type;
};

///Returns an unsigned integral type of at least the number of bytes specified
template <size_t BYTES>
struct uint_least {
  using type = typename uint_least<Math::ceilToPower(2, BYTES)>::type;
};

///Returns a signed integral type of at least the number of bytes specified
template <size_t BYTES>
using int_least_t = typename int_least<BYTES>::type;

///Returns an unsigned integral type of at least the number of bytes specified
template <size_t BYTES>
using uint_least_t = typename uint_least<BYTES>::type;

#define LEAST_BYTES(size, name) \
template <>\
struct int_least<size> {\
  using type = std::make_signed_t<name>;\
};\
\
template <>\
struct uint_least<size> {\
  using type = std::make_unsigned_t<name>;\
};

LEAST_BYTES(1, int8_t)
LEAST_BYTES(2, int16_t)
LEAST_BYTES(4, int32_t)
LEAST_BYTES(8, int64_t)

#if defined(__SIZEOF_INT128__) && __SIZEOF_INT128__ == 16
LEAST_BYTES(__SIZEOF_INT128__, __int128)
#endif

#undef LEAST_BYTES

///Returns a signed integral type of at least the sum of the size of the
///types specified
template <typename ...TYPES>
struct int_fit {
  using type = int_least_t<(sizeof(TYPES) + ...)>;
};

///Returns an unsigned integral type of at least the sum of the size of the
///types specified
template <typename ...TYPES>
struct uint_fit {
  using type = uint_least_t<(sizeof(TYPES) + ...)>;
};

///Returns a signed integral type of at least the sum of the size of the
///types specified
template <typename ...TYPES>
using int_fit_t = typename int_fit<TYPES...>::type;

///Returns an unsigned integral type of at least the sum of the size of the
///types specified
template <typename ...TYPES>
using uint_fit_t = typename uint_fit<TYPES...>::type;

#endif
