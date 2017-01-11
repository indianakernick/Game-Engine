//
//  circle.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_geometry_circle_hpp
#define engine_geometry_circle_hpp

#include "point.hpp"
#include <iostream>

namespace Geometry {
  class Circle {
  public:
    Circle() = default;
    Circle(int cx, int cy, int r);
    Circle(Point c, int r);
    
    friend std::ostream &operator<<(std::ostream &, const Circle &);
    friend std::ostream &operator<<(std::ostream &, const Circle &&);
    
    Rect bounds() const;
    
    Point c;
    int r {0};
  };
}

#endif
