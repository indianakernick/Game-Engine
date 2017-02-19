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

class Any;

template <>
struct std::hash<Any> {
  size_t operator()(const Any &) const;
};

class Any {
friend size_t std::hash<Any>::operator()(const Any &) const;
public:
  Any()
    : deleter(nullptr) {}
  Any(std::nullptr_t)
    : deleter(nullptr) {}
  template <typename T>
  Any(const T &val)
    : deleter(new DeleterImpl<T>(val)) {}
  
  Any(const Any &other) {
    if (other.deleter) {
      deleter = other.deleter->copy();
    }
  }
  
  Any &operator=(const Any &other) {
    if (!other.deleter) {
      deleter.reset();
      return *this;
    }
  
    if (!deleter || deleter->getTypeHash() != other.deleter->getTypeHash()) {
      deleter = other.deleter->make();
    }
    deleter->assign(other.deleter);
    return *this;
  }

  bool operator==(const Any &other) {
    return deleter->getTypeHash() == other.deleter->getTypeHash() &&
           deleter->compare(other.deleter);
  }
  bool operator!=(const Any &other) {
    return deleter->getTypeHash() != other.deleter->getTypeHash() ||
           !deleter->compare(other.deleter);
  }

  template <typename T>
  T &as() {
    assert(deleter);
    assert(is<T>());
    return *reinterpret_cast<T *>(deleter->getPtr());
  }
  
  template <typename T>
  const T &as() const {
    assert(deleter);
    assert(is<T>());
    return *reinterpret_cast<T *>(deleter->getPtr());
  }
  
  template <typename T>
  bool is() const {
    return deleter && typeid(T).hash_code() == deleter->getTypeHash();
  }
  
private:
  class Deleter {
  public:
    using Ptr = std::unique_ptr<Deleter>;
  
    Deleter() = default;
    virtual ~Deleter() = default;
    
    virtual size_t getValHash() const = 0;
    virtual size_t getTypeHash() const = 0;
    virtual void *getPtr() const = 0;
    virtual bool compare(const Ptr &) const = 0;
    virtual Ptr make() const = 0;
    virtual Ptr copy() const = 0;
    virtual void assign(const Ptr &) const = 0;
  };
  
  template <typename T>
  class DeleterImpl : public Deleter {
  public:
    DeleterImpl(const T &val)
      : ptr(new T(val)) {}
    ~DeleterImpl() {
      delete ptr;
    }
    
    size_t getValHash() const override {
      return hasher(*ptr);
    };
    size_t getTypeHash() const override {
      return TYPE_HASH;
    }
    void *getPtr() const override {
      return ptr;
    }
    bool compare(const Deleter::Ptr &other) const override {
      return *ptr == *dynamic_cast<DeleterImpl<T> *>(other.get())->ptr;
    }
    Deleter::Ptr make() const override {
      return Deleter::Ptr(new DeleterImpl<T>(T()));
    }
    Deleter::Ptr copy() const override {
      return Deleter::Ptr(new DeleterImpl<T>(*ptr));
    }
    void assign(const Deleter::Ptr &other) const override {
      *ptr = *dynamic_cast<DeleterImpl<T> *>(other.get())->ptr;
    }
    
  private:
    static const std::hash<T> hasher;
    static const size_t TYPE_HASH;
    T *ptr;
  };
  
  Deleter::Ptr deleter;
};

template <typename T>
const std::hash<T> Any::DeleterImpl<T>::hasher {};

template <typename T>
const size_t Any::DeleterImpl<T>::TYPE_HASH = typeid(T).hash_code();

#endif
