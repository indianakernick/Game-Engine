//
//  program factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 7/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "program factory.hpp"

#ifdef USE_OPENGL

Graphics3D::Program3D::Ptr Graphics3D::makeProgram3D() {
  return std::make_shared<ProgramOpenGL3D>();
}

#else

#error No implementation was found

#endif
