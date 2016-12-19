//
//  material3d.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "material.hpp"

Graphics3D::Material::Material(const FColor &diffuse, const FColor &ambient)
  : diffuse(diffuse), ambient(ambient) {}

float Graphics3D::Material::getAlpha() const {
  return diffuse.a;
}
