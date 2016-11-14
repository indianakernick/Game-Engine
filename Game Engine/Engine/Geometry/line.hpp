//
//  line.hpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef line_hpp
#define line_hpp

#include "point.hpp"

namespace Geometry {
  class Line {
  public:
    struct Graph {
      double m;
      double b;
      bool valid {true};
    };
  
    Line() = default;
    Line(int ax, int ay, int bx, int by);
    Line(Point a, Point b);
    
    ///Represent the object as a string for debug purposes
    std::string display() const;
    
    Point mid() const;
    Rect bounds() const;
    double length() const;
    int pxLength() const;
    ///Tests if the Line is vertical
    bool vert() const;
    ///Tests if the Line is horizontal
    bool hori() const;
    ///Calculates the information required to graph the Line in the
    ///form y=mx+b. Sets valid to false for vertical lines
    Graph graph() const;
    
    bool operator==(const Line&) const;
    bool operator!=(const Line&) const;
    
    Point a, b;
  };
}

#endif
