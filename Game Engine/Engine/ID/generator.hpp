//
//  generator.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_id_generator_hpp
#define engine_id_generator_hpp

#include <unordered_set>
#include <random>

namespace ID {
  template <typename T>
  class Generator {
  private:
    template <typename RET>
    using IsArithmetic = typename std::enable_if<std::is_arithmetic<T>::value, RET>::type;
  public:
    Generator() = default;
    
    auto create() -> IsArithmetic<T> {
      T id;
      do {
        id = dist(gen);
      } while (used.count(id));
      used.insert(id);
      return id;
    }
    auto remove(T id) -> IsArithmetic<void> {
      used.erase(id);
    }
    auto removeAll() -> IsArithmetic<void> {
      used.clear();
    }
    auto has(T id) -> IsArithmetic<bool> {
      return used.count(id);
    }
    auto reserve(T id) -> IsArithmetic<void> {
      used.insert(id);
    }
  
  private:
    std::unordered_set<T> used;
    
    static std::random_device gen;
    using DistType = typename std::conditional<std::is_integral<T>::value,
                                               std::uniform_int_distribution<T>,
                                               std::uniform_real_distribution<T>>::type;
    static DistType dist;
  };
  
  template <typename T>
  std::random_device Generator<T>::gen;
  
  template <typename T>
  typename Generator<T>::DistType Generator<T>::dist;
}

#endif
