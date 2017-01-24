//
//  type least bytes.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_type_least_bytes_hpp
#define engine_math_type_least_bytes_hpp

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace Math {
  ///Returns a type of at least the number of bytes specified
  template <size_t BYTES>
  struct TypeLeastBytes {};
  
  template <size_t BYTES>
  struct SignedTypeLeastBytes {
    using type = typename std::make_signed<typename TypeLeastBytes<BYTES>::type>::type;
  };
  
  template <size_t BYTES>
  struct UnsignedTypeLeastBytes {
    using type = typename std::make_unsigned<typename TypeLeastBytes<BYTES>::type>::type;
  };
  
  #define LEAST_BYTES(size, name) \
  template <>\
  struct TypeLeastBytes<size> {\
    using type = name;\
  };
  
  LEAST_BYTES(1, uint8_t)
  LEAST_BYTES(2, uint16_t)
  LEAST_BYTES(3, uint32_t)
  LEAST_BYTES(4, uint32_t)
  LEAST_BYTES(5, uint64_t)
  LEAST_BYTES(6, uint64_t)
  LEAST_BYTES(7, uint64_t)
  LEAST_BYTES(8, uint64_t)
  
  #if defined(__SIZEOF_INT128__) && __SIZEOF_INT128__ == 16
  LEAST_BYTES(9, unsigned __int128)
  LEAST_BYTES(10, unsigned __int128)
  LEAST_BYTES(11, unsigned __int128)
  LEAST_BYTES(12, unsigned __int128)
  LEAST_BYTES(13, unsigned __int128)
  LEAST_BYTES(14, unsigned __int128)
  LEAST_BYTES(15, unsigned __int128)
  LEAST_BYTES(16, unsigned __int128)
  #endif
  
  #undef LEAST_BYTES
}

#endif
