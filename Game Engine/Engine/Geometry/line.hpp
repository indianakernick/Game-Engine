//
//  line.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_geometry_line_hpp
#define engine_geometry_line_hpp

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
    
    friend std::ostream &operator<<(std::ostream &stream, const Line &line);
    friend std::ostream &operator<<(std::ostream &stream, const Line &&line);
    
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
