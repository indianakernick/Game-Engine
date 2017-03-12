//
//  program type.cpp
//  Game Engine
//
//  Created by Indi Kernick on 12/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "program type.hpp"

bool Graphics3D::ProgType::operator==(ProgType other) const {
  return (ui && other.ui) || (
    ui == other.ui &&
    anim == other.anim &&
    frag == other.frag
  );
}

bool Graphics3D::ProgType::operator!=(ProgType other) const {
  return !(*this == other);
}

size_t std::hash<Graphics3D::ProgType>::operator()(const Graphics3D::ProgType val) const {
  if (val.ui) {
    //if the program is a ui program then the other properties should be ignored
    //so we need a unique value to represent a ui program. All other values
    //represent 3d programs
    return std::numeric_limits<size_t>::max();
  } else {
    return hashCombine(val.anim, val.frag);
  }
}
