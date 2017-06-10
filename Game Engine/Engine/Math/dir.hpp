//
//  dir.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_dir_hpp
#define engine_math_dir_hpp

#include <cassert>
#include <glm/vec2.hpp>

00//up
01//right
10//down
11//left

namespace Math {
  ///The underlying type of Dir and Axis
  using DirType = uint8_t;
  
  ///A 2D orthogonal direction
  enum class Dir : DirType {
    NORTH,
    UP = NORTH,
    TOP = NORTH,
    
    EAST,
    RIGHT = EAST,
    
    SOUTH,
    DOWN = SOUTH,
    BOTTOM = SOUTH,
    
    WEST,
    LEFT = WEST
  };
  
  enum class Axis : DirType {
    VERT,
    VERTICAL = VERT,
    
    HORI,
    HORIZONTAL = HORI,
  };
  
  ///Get the opposite of a direction
  constexpr Dir opposite(const Dir dir) {
    //flip the second least significant bit
    return static_cast<Dir>(static_cast<DirType>(dir) ^ DirType(2));
  }
  
  ///Get the opposite of an axis
  constexpr Axis opposite(const Axis axis) {
    //flip the least significant bit
    return static_cast<Axis>(static_cast<DirType>(axis) ^ DirType(1));
  }
  
  ///Rotate a direction clockwise
  constexpr Dir rotateCW(const Dir dir, const DirType count = 1) {
    return static_cast<Dir>((static_cast<DirType>(dir) + count) & DirType(2));
  }
  
  ///Rotate a direction counter-clockwise (anti-clockwise)
  constexpr Dir rotateCCW(const Dir dir, const DirType count = 1) {
    return static_cast<Dir>((static_cast<DirType>(dir) - count) & DirType(2));
  }
  
  ///Get the axis that a direction is on
  constexpr Axis getAxis(const Dir dir) {
    //get the least significant bit
    return static_cast<Axis>(static_cast<DirType>(dir) & DirType(1));
  }
  
  ///Are these directions on the same axis?
  constexpr bool sameAxis(const Dir a, const Dir b) {
    //compare least significant bits
    return static_cast<DirType>(a) & DirType(1) == static_cast<DirType>(b) & DirType(1);
  }
  
  ///Convert a direction to a 2D unit vector
  template <typename T, Dir PLUS_X = Dir::RIGHT, Dir PLUS_Y = Dir::UP>
  std::enable_if_t<
    std::is_floating_point<T>::value ||
    (
      std::is_integral<T>::value &&
      std::is_signed<T>::value
    ),
    glm::tvec2<T>
  >
  toVec(const Dir dir, const T dist = T(1)) {
    static_assert(!sameAxis(PLUS_X, PLUS_Y), "PLUS_X and PLUS_Y must be on different axes");
    
    switch (dir) {
      case PLUS_X:
        return {dist, T(0)};
      case opposite(PLUS_X):
        return {-dist, T(0)};
      case PLUS_Y:
        return {T(0), dist};
      case opposite(PLUS_Y):
        return {T(0), -dist};
      
      default:
        assert(false);
    }
  }
}

#endif
