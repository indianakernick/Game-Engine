//
//  shader path.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader path.hpp"

Res::ID getVert(Graphics3D::ProgType program) {
  if (program.ui) {
    return Res::ID("Shaders/Interpolation/ui.vert");
  } else {
    if (program.anim) {
      return Res::ID("Shaders/Interpolation/phong anim.vert");
    } else {
      return Res::ID("Shaders/Interpolation/phong no anim.vert");
    }
  }
}

Res::ID getFrag(Graphics3D::ProgType program) {
  if (program.ui) {
    return Res::ID("Shaders/Interpolation/ui.frag");
  } else {
    Res::ID otherFile;
    
    switch (program.frag) {
      case Graphics3D::FragType::PHONG:
        otherFile = "Shaders/Lighting/phong.glsl";
        break;
      case Graphics3D::FragType::BLINN:
        otherFile = "Shaders/Lighting/blinn.glsl";
        break;
      case Graphics3D::FragType::TOON:
        otherFile = "Shaders/Lighting/toon.glsl";
        break;
      case Graphics3D::FragType::OREN_NAYER:
        otherFile = "Shaders/Lighting/oren nayer.glsl";
        break;
      case Graphics3D::FragType::MINNAERT:
        otherFile = "Shaders/Lighting/minnaert.glsl";
        break;
      case Graphics3D::FragType::COOK_TORRANCE:
        otherFile = "Shaders/Lighting/cook torrance.glsl";
        break;
      case Graphics3D::FragType::SOLID:
        otherFile = "Shaders/Lighting/solid.glsl";
        break;
      case Graphics3D::FragType::FRESNEL:
        otherFile = "Shaders/Lighting/fresnel.glsl";
        break;
    }
    
    return Res::ID("Shaders/Interpolation/phong.frag", otherFile);
  }
}

Graphics3D::Shaders Graphics3D::getShaders(Graphics3D::ProgType program) {
  return {getVert(program), getFrag(program)};
}
