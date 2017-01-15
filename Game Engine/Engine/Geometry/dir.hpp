//
//  dir.hpp
//  Game Engine
//
//  Created by Indi Kernick on 26/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_geometry_dir_hpp
#define engine_geometry_dir_hpp

#include <cstdint>
#include <iostream>

namespace Geometry {
  typedef uint8_t DirType;
  enum class Dir : DirType {
    UP,
    RIGHT,
    DOWN,
    LEFT
  };
  typedef uint8_t SideType;
  enum class Side : SideType {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
  };
  inline DirType invert(DirType dir) {
    return (dir + 2) & 3;
  }
  /*inline SideType invert(SideType dir) {
    return (side + 2) & 3;
  }*/
  inline Dir invert(Dir dir) {
    return static_cast<Dir>(invert(static_cast<DirType>(dir)));
  }
  inline Side invert(Side side) {
    return static_cast<Side>(invert(static_cast<SideType>(side)));
  }
  
  inline DirType toNum(Dir dir) {
    return static_cast<DirType>(dir);
  }
  inline SideType toNum(Side side) {
    return static_cast<SideType>(side);
  }
  inline void validate(DirType& dir) {
    dir &= 3;
  }
  /*inline void validate(SideType& side) {
    side &= 3;
  }*/
  
  std::ostream &operator<<(std::ostream &stream, Dir);
  std::ostream &operator<<(std::ostream &stream, Side);
};

#endif
