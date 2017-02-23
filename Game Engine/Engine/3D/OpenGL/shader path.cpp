//
//  shader path.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader path.hpp"

Graphics3D::Shaders Graphics3D::getShaders(Graphics3D::ProgType program) {
  Shaders out;
  
  std::string vertShaderPath = "Shaders/Interpolation/phong";
  
  if (program.anim) {
    vertShaderPath += " anim.vert";
  } else {
    vertShaderPath += " no anim.vert";
  }
  
  out.vert = Res::ID(vertShaderPath);
  
  Res::ID otherFile;
  
  switch (program.frag) {
    case FragType::PHONG:
      otherFile = "Shaders/Lighting/phong.glsl";
      break;
    case FragType::BLINN:
      otherFile = "Shaders/Lighting/blinn.glsl";
      break;
    case FragType::TOON:
      otherFile = "Shaders/Lighting/toon.glsl";
      break;
    case FragType::OREN_NAYER:
      otherFile = "Shaders/Lighting/oren nayer.glsl";
      break;
    case FragType::MINNAERT:
      otherFile = "Shaders/Lighting/minnaert.glsl";
      break;
    case FragType::COOK_TORRANCE:
      otherFile = "Shaders/Lighting/cook torrance.glsl";
      break;
    case FragType::SOLID:
      otherFile = "Shaders/Lighting/solid.glsl";
      break;
    case FragType::FRESNEL:
      otherFile = "Shaders/Lighting/fresnel.glsl";
      break;
  }
  
  out.frag = Res::ID("Shaders/Interpolation/phong.frag", otherFile);
  
  return out;
}
