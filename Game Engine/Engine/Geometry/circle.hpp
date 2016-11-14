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
#include <iostream>

namespace Geometry {
  class Circle {
  public:
    Circle() = default;
    Circle(int cx, int cy, int r);
    Circle(Point c, int r);
    
    friend std::ostream &operator<<(std::ostream &, Circle &);
    
    Rect bounds() const;
    
    Point c;
    int r {0};
  };
}

#endif
