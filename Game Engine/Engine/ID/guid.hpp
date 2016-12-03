//
//  guid.hpp
//  Game Engine
//
//  Created by Indi Kernick on 3/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef guid_hpp
#define guid_hpp

#include <random>
#include <unordered_set>

namespace ID {
  template <typename T>
  class GUID {
  public:
    GUID() = delete;
    ~GUID() = delete;
    
    static auto get() -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
      T newID;
      do {
        newID = dist(gen);
      } while (used.count(newID));
      used.insert(newID);
      return newID;
    }
  private:
    static std::unordered_set<T> used;
    static std::random_device gen;
    using DistType = typename std::conditional<std::is_integral<T>::value,
                                               std::uniform_int_distribution<T>,
                                               std::uniform_real_distribution<T>>::type;
    static DistType dist;
  };
  
  template <typename T>
  std::unordered_set<T> GUID<T>::used;

  template <typename T>
  std::random_device GUID<T>::gen;

  template <typename T>
  typename GUID<T>::DistType GUID<T>::dist;
}

#endif
