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

void writeFontMetrics(YAML::Emitter &emitter, const FaceMetrics &metrics) {
  emitter <<
  YAML::BeginMap <<
    YAML::Key << "line height" << YAML::Value << metrics.lineHeight <<
    YAML::Key << "min y" << YAML::Value << metrics.minY <<
    YAML::Key << "max y" << YAML::Value << metrics.maxY <<
  YAML::EndMap;
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

void writeAtlas(
  const std::string &output,
  const Face &face,
  SizePx texSize
) {
  PROFILE(writeAtlas(Font));
  
  std::cout << "Writing atlas to file \"" << output << "\"\n";
  
  std::ofstream file(output);
  YAML::Emitter emitter(file);
  
  checkEmitter(emitter);
  
  emitter << YAML::BeginDoc << YAML::BeginMap <<
    YAML::Key << "type" << YAML::Value << "font" <<
    YAML::Key << "size" << YAML::Value << YAML::Flow << YAML::BeginSeq <<
      texSize << texSize <<
    YAML::EndSeq <<
    YAML::Key << "range" << YAML::Value << YAML::Flow << YAML::BeginSeq <<
      face.range.begin << face.range.end <<
    YAML::EndSeq <<
    YAML::Key << "font metrics" << YAML::Value;
  
  writeFontMetrics(emitter, face.faceMetrics);
  
  emitter <<
    YAML::Key << "glyph metrics" << YAML::Value;
  
  writeMetrics(emitter, face.glyphMetrics);
  
  emitter <<
    YAML::Key << "glyphs" << YAML::Value;
  
  writeGlyphs(emitter, face.glyphs);
  
  if (face.kerning.size()) {
    emitter <<
      YAML::Key << "has kerning" << YAML::Value << true <<
      YAML::Key << "kerning" << YAML::Value << face.kerning;
  } else {
    emitter <<
      YAML::Key << "has kerning" << YAML::Value << false;
  }
  
  emitter << YAML::EndMap << YAML::EndDoc;
  
  checkEmitter(emitter);
}
