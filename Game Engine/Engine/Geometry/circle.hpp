//
//  circle.hpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef circle_hpp
#define circle_hpp

#include "point.hpp"
#include <string>

namespace Geometry {
  class Circle {
  public:
    Circle() = default;
    Circle(int cx, int cy, int r);
    Circle(Point c, int r);
    
    ///Represent the object as a string for debug purposes
    std::string display() const;
    
    Rect bounds() const;
    
    Point c;
    int r {0};
  };
}

#endif