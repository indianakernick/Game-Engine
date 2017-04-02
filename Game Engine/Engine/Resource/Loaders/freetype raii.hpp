//
//  freetype raii.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_freetype_raii_hpp
#define engine_resource_loaders_freetype_raii_hpp

#include "freetype log error.hpp"
#include <utility>

template <typename T>
class FTHandle {
private:
  using Deleter = FT_Error(*)(T);
public:
  FTHandle() = delete;
  FTHandle(Deleter deleter)
    : obj(nullptr), deleter(deleter) {
    assert(deleter);
  }
  FTHandle(const FTHandle &) = delete;
  FTHandle(FTHandle &&other) {
    obj = other.obj;
    deleter = other.deleter;
    other.obj = nullptr;
  }
  ~FTHandle() {
    if (obj) {
      LOG_FT_ERROR(deleter(obj));
    }
  }
  
  FTHandle &operator=(const FTHandle &) = delete;
  FTHandle &operator=(FTHandle &&other) {
    if (obj) {
      LOG_FT_ERROR(deleter(obj));
    }
    obj = other.obj;
    deleter = other.deleter;
    other.obj = nullptr;
    return *this;
  }
  
  void swap(FTHandle &other) {
    std::swap(deleter, other.deleter);
    std::swap(obj, other.obj);
  }
  
  explicit operator bool() {
    return obj;
  }
  operator T() const {
    return obj;
  }
  bool operator!() {
    return !obj;
  }
  T operator->() {
    return obj;
  }
  T *operator&() {
    return &obj;
  }
private:
  T obj;
  Deleter deleter;
};

#endif
