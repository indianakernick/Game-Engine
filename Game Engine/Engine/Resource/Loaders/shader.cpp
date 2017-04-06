//
//  shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader.hpp"

const std::string &Res::ShaderLoader::getName() const {
  static const std::string NAME = "Shader";
  return NAME;
}

bool Res::ShaderLoader::canLoad(std::experimental::string_view ext) const {
  return ext == "vert" ||
         ext == "frag" ||
         ext == "geom";
}

Res::Handle::Ptr Res::ShaderLoader::load(const ID &id) const {
  const Platform::Shader::Type type = getType(id.getExt());
  const Any &data = id.getData();
  const Memory::Buffer file = readFile(id);
  size_t sourceLength = file.size();
  Platform::Shader::Ptr shader;
  
  if (data.is<Res::ID>()) {
    const Memory::Buffer otherFile = readFile(data.as<Res::ID>());
    sourceLength += otherFile.size();
    shader = Platform::makeShader(file, otherFile, type);
  } else {
    shader = Platform::makeShader(file, type);
  }
  
  Res::Handle::Ptr handle = std::make_shared<Shader>(shader);
  handle->setSize(sourceLength);
  
  return handle;
}

Platform::Shader::Type Res::ShaderLoader::getType(std::experimental::string_view ext) {
  if (ext == "vert") {
    return Platform::Shader::Type::VERTEX;
  } else if (ext == "frag") {
    return Platform::Shader::Type::FRAGMENT;
  } else {
    return Platform::Shader::Type::GEOMETRY;
  }
}
