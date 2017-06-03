//
//  type.hpp
//  Game Engine
//
//  Created by Indi Kernick on 3/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_id_type_hpp
#define engine_id_type_hpp

#include <type_traits>

namespace ID {
  template <typename Int>
  class Counter {
  
    static_assert(std::is_integral<Int>::value, "Int must be an integral type");
  
  public:
    Counter() = delete;
    ~Counter() = delete;
  
  //Friend declarations shall not declare partial specializations
  protected:
    static Int counter;
  };
  
  template <typename Int>
  Int Counter<Int>::counter = 0;
  
  ///Creates an ID unique to the type. IDs are counted and only
  ///available at runtime
  template <typename Int, typename T>
  class TypeCounter : private Counter<Int> {
  
    static_assert(std::is_integral<Int>::value, "Int must be an integral type");
  
  public:
    TypeCounter() = delete;
    ~TypeCounter() = delete;
    
    static Int get() {
      return ID;
    }
    
  private:
    static const Int ID;
  };
  
  template <typename Int, typename T>
  const Int TypeCounter<Int, T>::ID = Counter<Int>::counter++;
  
  template <typename T>
  class Hasher {
  public:
    Hasher() = delete;
    ~Hasher() = delete;
    
  protected:
    //@TODO the ctti library does this by hashing __PRETTY_FUNCTION__
    static void dummy() {}
    static constexpr void (*HASH)() = &Hasher::dummy;
  };
  
  template <typename Int, typename T>
  class TypeHasher : private Hasher<T> {
  
    static_assert(std::is_integral<Int>::value, "Int must be an integral type");
  
  public:
    TypeHasher() = delete;
    ~TypeHasher() = delete;
    
    static constexpr Int get() {
      return ID;
    }
    
  private:
    static constexpr Int ID = reinterpret_cast<Int>(Hasher<T>::HASH);
  };
}

#endif
