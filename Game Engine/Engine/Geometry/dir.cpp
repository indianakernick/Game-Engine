//
//  dir.cpp
//  game engine
//
//  Created by Indi Kernick on 26/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "dir.hpp"

std::ostream &Geometry::operator<<(std::ostream &stream, Geometry::Dir dir) {
  switch (dir) {
    case Geometry::Dir::UP:
      return stream << "UP";
    case Geometry::Dir::RIGHT:
      return stream << "RIGHT";
    case Geometry::Dir::DOWN:
      return stream << "DOWN";
    case Geometry::Dir::LEFT:
      return stream << "LEFT";
  }
}

std::ostream &Geometry::operator<<(std::ostream &stream, Geometry::Side dir) {
  switch (dir) {
    case Geometry::Side::TOP:
      return stream << "TOP";
    case Geometry::Side::RIGHT:
      return stream << "RIGHT";
    case Geometry::Side::BOTTOM:
      return stream << "BOTTOM";
    case Geometry::Side::LEFT:
      return stream << "LEFT";
  }
}
