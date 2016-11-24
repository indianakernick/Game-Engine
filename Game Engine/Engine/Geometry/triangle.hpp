//
//  triangle.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

#include "point.hpp"
#include "rect.hpp"
#include "line.hpp"
#include <string>

namespace Geometry {
  class Triangle {
  public:
    struct Sides {
      Line a;
      Line b;
      Line c;
    };
  
    Triangle() = default;
    Triangle(int ax, int ay, int bx, int by, int cx, int cy);
    Triangle(Point a, Point b, Point c);
    
    
    friend std::ostream &operator<<(std::ostream &stream, Triangle &tri);
    
    Rect bounds() const;
    Point mid() const;
    Sides sides() const;
    
    Point a, b, c;
  };
}

#endif
