//
//  singleton.hpp
//  game engine
//
//  Created by Indi Kernick on 8/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef singleton_hpp
#define singleton_hpp

#include <utility>
#include <cassert>

template <typename T>
class Singleton {
public:
  template <typename ...ARGS>
  static void init(ARGS ...args) {
    assert(instance == nullptr);
    instance = new T(std::forward<ARGS>(args)...);
    assert(instance != nullptr);
  }
  static T &get() {
    assert(instance != nullptr);
    return *instance;
  }
  static void destroy() {
    assert(instance != nullptr);
    delete instance;
    instance = nullptr;
  }
private:
  static T *instance;
};

template<typename T>
T *Singleton<T>::instance = nullptr;

#endif