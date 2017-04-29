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

AtlasWriteError::AtlasWriteError(const std::string &error)
  : std::runtime_error("Failed to write atlas to file: " + error) {}

void checkEmitter(const YAML::Emitter &emitter) {
  if (!emitter.good()) {
    throw AtlasWriteError(emitter.GetLastError());
  }
}

std::string getImageName(const std::string &path) {
  const size_t lastSlash = path.find_last_of('/');
  return path.substr(lastSlash + 1, path.find_last_of('.') - lastSlash - 1);
}

void writeHead(YAML::Emitter &emitter, const std::string &type, int length) {
  emitter <<
  YAML::Key << "head" << YAML::Value <<
    YAML::BeginMap <<
      YAML::Key << "type" << YAML::Value << type <<
      YAML::Key << "texture size" << YAML::Value <<
        YAML::Flow << YAML::BeginSeq << length << length << YAML::EndSeq <<
    YAML::EndMap;
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

void writeGlyphs(YAML::Emitter &emitter, const std::vector<Image> &images) {
  emitter << YAML::BeginSeq;
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    if (i->s.x == 0 || i->s.y == 0) {
      emitter << YAML::Flow << YAML::BeginSeq << 0 << 0 << 0 << 0 << YAML::EndSeq;
    } else {
      emitter << YAML::Flow << YAML::BeginSeq <<
        i->p.x <<
        i->p.y <<
        (i->p.x + i->s.x - 1) <<
        (i->p.y + i->s.y - 1) <<
      YAML::EndSeq;
    }
  }
  emitter << YAML::EndSeq;
}

void writeMetrics(YAML::Emitter &emitter, const std::vector<GlyphMetrics> &metrics) {
  emitter << YAML::BeginSeq;
  for (auto m = metrics.cbegin(); m != metrics.cend(); m++) {
    emitter <<
    YAML::BeginMap <<
      YAML::Key << "bearing" << YAML::Value <<
        YAML::Flow << YAML::BeginSeq << m->bearing.x << m->bearing.y << YAML::EndSeq <<
      YAML::Key << "size" << YAML::Value <<
        YAML::Flow << YAML::BeginSeq << m->size.x << m->size.y << YAML::EndSeq <<
      YAML::Key << "advance" << YAML::Value << m->advance <<
    YAML::EndMap;
  }
  emitter << YAML::EndSeq;
}

void writeKerning(YAML::Emitter &emitter, const std::vector<int> &kerning) {
  emitter << kerning;
}

void writeFontMetrics(YAML::Emitter &emitter, const Font::Metrics &metrics) {
  emitter <<
  YAML::BeginMap <<
    YAML::Key << "line height" << YAML::Value << metrics.lineHeight <<
    YAML::Key << "min y" << YAML::Value << metrics.minY <<
    YAML::Key << "max y" << YAML::Value << metrics.maxY <<
  YAML::EndMap;
}

void writeAtlas(const std::string &path, const std::vector<Image> &images, int length) {
  std::cout << "Writing atlas to file \"" << path << "\"\n";
  
  std::ofstream file(path);
  YAML::Emitter emitter(file);
  
  checkEmitter(emitter);
  
  emitter << YAML::BeginDoc << YAML::BeginMap;
  
  writeHead(emitter, "image", length);
  
  emitter << YAML::Key << "body" << YAML::Value;
  writeImages(emitter, images);
  
  emitter << YAML::EndMap << YAML::EndDoc;
  
  checkEmitter(emitter);
}

void writeAtlas(
  const std::string &path,
  const Font &font,
  const Glyphs &glyphs,
  int length
) {
  std::cout << "Writing atlas to file \"" << path << "\"\n";
  
  std::ofstream file(path);
  YAML::Emitter emitter(file);
  
  emitter << YAML::BeginDoc << YAML::BeginMap;
  
  writeHead(emitter, "font", length);
  
  emitter <<
  YAML::Key << "body" << YAML::Value <<
    YAML::BeginSeq <<
      YAML::BeginMap <<
        YAML::Key << "range" << YAML::Value <<
          YAML::Flow << YAML::BeginSeq <<
            glyphs.begin <<
            glyphs.end <<
          YAML::EndSeq <<
        YAML::Key << "font metrics" << YAML::Value;
  
  writeFontMetrics(emitter, font.metrics);
  
  emitter <<
        YAML::Key << "glyph metrics" << YAML::Value;
  
  writeMetrics(emitter, glyphs.metrics);
  
  emitter <<
        YAML::Key << "glyphs" << YAML::Value;
  
  writeGlyphs(emitter, glyphs.images);
  
  if (glyphs.kerning.size()) {
    emitter <<
        YAML::Key << "has kerning" << YAML::Value << true <<
        YAML::Key << "kerning" << YAML::Value;
    
    writeKerning(emitter, glyphs.kerning);
  } else {
    emitter <<
        YAML::Key << "has kerning" << YAML::Value << false;
  }
  
  emitter <<
      YAML::EndMap <<
    YAML::EndSeq;
  
  emitter << YAML::EndMap << YAML::EndDoc;
}
