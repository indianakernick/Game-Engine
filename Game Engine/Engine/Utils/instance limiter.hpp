//
//  instance limiter.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_instance_limiter_hpp
#define engine_utils_instance_limiter_hpp

#ifdef ENABLE_INSTANCE_LIMITER

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include "type name.hpp"

///Limit the number of instances of a derived class
template <typename T, size_t MAX_COUNT>
class LimitInstances {
private:
  static void checkCount() {
    if (count > MAX_COUNT) {
      std::printf(
        "Too many instances of type %s\nMaximum is %lu\n",
        typeName<T>().c_str(),
        MAX_COUNT
      );
      std::abort();
    }
  }

protected:
  LimitInstances() {
    count++;
    checkCount();
  }
  LimitInstances(const LimitInstances &) {
    count++;
    checkCount();
  }
  LimitInstances(LimitInstances &&) {
    count++;
  }
  ~LimitInstances() {
    count--;
  }
  
  LimitInstances &operator=(const LimitInstances &) = default;
  LimitInstances &operator=(LimitInstances &&) = default;

private:
  static size_t count;
};

template <typename T, size_t MAX_COUNT>
size_t LimitInstances<T, MAX_COUNT>::count = 0;

///Limit the number of instances of a derived class
template <typename T>
class LimitInstances<T, 1> {
protected:
  LimitInstances() {
    if (created) {
      std::printf(
        "Too many instances of singleton type %s\n",
        typeName<T>().c_str()
      );
      std::abort();
    } else {
      created = true;
    }
  }
  LimitInstances(const LimitInstances &) = delete;
  LimitInstances(LimitInstances &&) = delete;
  ~LimitInstances() {
    created = false;
  }
  
  LimitInstances &operator=(const LimitInstances &) = delete;
  LimitInstances &operator=(LimitInstances &&) = delete;

private:
  static bool created;
};

template <typename T>
bool LimitInstances<T, 1>::created = false;

#else

#include <cstddef>

///Limit the number of instances of a derived class
template <typename, size_t>
class LimitInstances {
protected:
  LimitInstances() = default;
  LimitInstances(const LimitInstances &) = default;
  LimitInstances(LimitInstances &&) = default;
  ~LimitInstances() = default;
  
  LimitInstances &operator=(const LimitInstances &) = default;
  LimitInstances &operator=(LimitInstances &&) = default;
};

///Limit the number of instances of a derived class
template <typename T>
class LimitInstances<T, 1> {
protected:
  LimitInstances() = default;
  LimitInstances(const LimitInstances &) = delete;
  LimitInstances(LimitInstances &&) = default;
  ~LimitInstances() = default;
  
  LimitInstances &operator=(const LimitInstances &) = delete;
  LimitInstances &operator=(LimitInstances &&) = delete;
};

#endif

//I don't think there is any point in this

///Limit the number of instances of a derived class
template <typename T>
class LimitInstances<T, 0> {
protected:
  LimitInstances() = delete;
  LimitInstances(const LimitInstances &) = delete;
  LimitInstances(LimitInstances &&) = delete;
  ~LimitInstances() = delete;
  
  LimitInstances &operator=(const LimitInstances &) = delete;
  LimitInstances &operator=(LimitInstances &&) = delete;
};

///Force a derived class to be a singleton
template <typename T>
using ForceSingleton = LimitInstances<T, 1>;

#endif
