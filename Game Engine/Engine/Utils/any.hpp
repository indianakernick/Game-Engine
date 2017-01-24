//
//  any.hpp
//  Game Engine
//
//  Created by Indi Kernick on 25/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_any_hpp
#define engine_utils_any_hpp

#include <typeinfo>
#include <cassert>
#include <memory>

class Any {
public:
  template <typename T>
  Any(T *ptr)
    : deleter(new DeleterImpl<T>(ptr)) {}
  Any(std::nullptr_t)
    : deleter(nullptr) {}

  template <typename T>
  T *as() {
    assert(typeid(T).hash_code() == deleter->getType());
    return reinterpret_cast<T *>(deleter->getPtr());
  }
  
private:
  class Deleter {
  public:
    Deleter() = default;
    virtual ~Deleter() = default;
    
    virtual size_t getType() const = 0;
    virtual void *getPtr() const = 0;
  };
  
  template <typename T>
  class DeleterImpl : public Deleter {
  public:
    DeleterImpl(T *ptr)
      : ptr(ptr), type(typeid(T).hash_code()) {}
    ~DeleterImpl() {
      delete ptr;
    }
    
    size_t getType() const override {
      return type;
    }
    void *getPtr() const override {
      return ptr;
    }
    
  private:
    T *ptr;
    size_t type;
  };
  
  std::shared_ptr<Deleter> deleter;
};

#endif
