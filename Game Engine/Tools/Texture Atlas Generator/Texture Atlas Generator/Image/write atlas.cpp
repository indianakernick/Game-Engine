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
#include "../profiler.hpp"

std::string getImageName(const std::string &path) {
  const size_t lastSlash = path.find_last_of('/');
  return path.substr(lastSlash + 1, path.find_last_of('.') - lastSlash - 1);
}

void writeImages(YAML::Emitter &emitter, const std::vector<Image> &images, bool hasWhitepixel) {
  emitter << YAML::BeginMap;
  auto end = images.cend();
  if (hasWhitepixel) {
    end--;
  }
  for (auto i = images.cbegin(); i != end; i++) {
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
  Length size,
  bool hasWhitepixel
) {
  PROFILE(writeAtlas(Image));

  std::cout << "Writing atlas to file \"" << output << "\"\n";
  
  std::ofstream file(output);
  YAML::Emitter emitter(file);
  
  checkEmitter(emitter);
  
  emitter << YAML::BeginDoc << YAML::BeginMap <<
    YAML::Key << "type" << YAML::Value << "image" <<
    YAML::Key << "size" << YAML::Value << YAML::Flow << YAML::BeginSeq <<
      size << size <<
    YAML::EndSeq;
  
  if (hasWhitepixel) {
    const ivec2 pos = {
      images.back().p.x + (images.back().s.x - 1) / 2,
      images.back().p.y + (images.back().s.y - 1) / 2
    };
    emitter <<
      YAML::Key << "whitepixel" << YAML::Value << YAML::Flow << YAML::BeginSeq <<
        pos.x << pos.y <<
      YAML::EndSeq;
  }
  
  emitter <<
    YAML::Key << "images" << YAML::Value;
  
  writeImages(emitter, images, hasWhitepixel);
  
  emitter << YAML::EndMap << YAML::EndDoc;
  
  checkEmitter(emitter);
}
