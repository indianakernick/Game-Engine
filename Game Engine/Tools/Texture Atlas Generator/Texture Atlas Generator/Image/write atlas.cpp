//
//  write atlas.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 4/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "write atlas.hpp"

#include "../write atlas.hpp"
#include <iostream>
#include <fstream>

std::string getImageName(const std::string &path) {
  const size_t lastSlash = path.find_last_of('/');
  return path.substr(lastSlash + 1, path.find_last_of('.') - lastSlash - 1);
}

void writeImages(YAML::Emitter &emitter, const std::vector<Image> &images) {
  emitter << YAML::BeginMap;
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    emitter << YAML::Key << getImageName(i->path) << YAML::Value <<
      YAML::Flow << YAML::BeginSeq <<
        i->p.x <<
        i->p.y <<
        (i->p.x + i->s.x - 1) <<
        (i->p.y + i->s.y - 1) <<
      YAML::EndSeq;
  }
  emitter << YAML::EndMap;
}

void writeAtlas(
  const std::string &output,
  const std::vector<Image> &images,
  Length size
) {
  std::cout << "Writing atlas to file \"" << output << "\"\n";
  
  std::ofstream file(output);
  YAML::Emitter emitter(file);
  
  checkEmitter(emitter);
  
  emitter << YAML::BeginDoc << YAML::BeginMap <<
    YAML::Key << "type" << YAML::Value << "image" <<
    YAML::Key << "size" << YAML::Value << YAML::Flow << YAML::BeginSeq <<
      size << size <<
    YAML::EndSeq <<
    YAML::Key << "images" << YAML::Value;
  
  writeImages(emitter, images);
  
  emitter << YAML::EndMap << YAML::EndDoc;
  
  checkEmitter(emitter);
}
