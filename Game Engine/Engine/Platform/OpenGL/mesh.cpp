//
//  mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "mesh.hpp"

#ifdef USE_OPENGL

using namespace Platform;

bool MeshImpl::isAnimated() const {
  return idWeights.size();
}

size_t MeshImpl::getByteSize() const {
  return byteSize;
}

#endif
