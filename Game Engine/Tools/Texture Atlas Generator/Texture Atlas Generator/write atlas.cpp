//
//  write atlas.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "write atlas.hpp"

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>

AtlasWriteError::AtlasWriteError(const std::string &path, const std::string &error)
  : std::runtime_error("Failed to write image \"" + path + "\" to atlas: " + error) {}

std::string getImageName(const std::string &path) {
  const size_t lastSlash = path.find_last_of('/');
  return path.substr(lastSlash + 1, path.find_last_of('.') - lastSlash - 1);
}

void writeAtlas(const std::string &path, const std::vector<Image> &images, int length) {
  std::cout << "Writing atlas to file \"" << path << "\"\n";
  
  std::ofstream file(path);
  YAML::Emitter emitter(file);
  
  emitter <<
  YAML::BeginDoc <<
    YAML::BeginMap <<
      YAML::Key << "head" << YAML::Value <<
      YAML::BeginMap <<
        YAML::Key << "texture size" << YAML::Value <<
        YAML::BeginSeq << length << length << YAML::EndSeq <<
      YAML::EndMap <<
      YAML::Key << "body" << YAML::Value <<
        YAML::BeginMap;
  
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    emitter << YAML::Key << getImageName(i->path) << YAML::Value <<
      YAML::BeginSeq << i->x << i->y << (i->x + i->w) << (i->y + i->h) << YAML::EndSeq;
    
    if (!emitter.good()) {
      throw AtlasWriteError(i->path, emitter.GetLastError());
    }
  }
  
  emitter <<
      YAML::EndMap <<
    YAML::EndMap <<
  YAML::EndDoc;
}
