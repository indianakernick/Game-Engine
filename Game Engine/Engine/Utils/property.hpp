//
//  property.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_property_hpp
#define engine_utils_property_hpp

#include <cassert>

template <typename T, int PERMISSIONS>
class Property {
private:
  static T &defaultGetter(T &val) {
    return val;
  }
  static T &defaultSetter(const T &other) {
    return other;
  }

public:
  using Getter = T &(T &);
  using Setter = T &(const T &);
  
  enum {
    READ = 1,
    WRITE = 2
  };
  
  Property() = default;
  Property(Getter *getter, Setter *setter)
    : getter(getter), setter(setter) {
    assert(getter);
    assert(setter);
  }
  Property(const T &val, Getter *getter, Setter *setter)
    : val(val), getter(getter), setter(setter) {
    assert(getter);
    assert(setter);
  }
  
  //it just gets messy if we return a reference to the property or tha value
  void operator=(const T &newVal) {
    static_assert(PERMISSIONS & WRITE, "Property doesn't have writing permissions");
    val = setter(newVal);
    return *this;
  }
  
  operator T() {
    static_assert(PERMISSIONS & READ, "Property doesn't have reading permissions");
    return getter(val);
  }
private:
  T val {};
  Getter *getter = &defaultGetter;
  Setter *setter = &defaultSetter;
};

#endif
