//
//  user interface.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 3/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "user interface.hpp"

#include <yaml-cpp/yaml.h>
#include <iostream>
#include "load font.hpp"
#include "load glyphs.hpp"
#include "../math.hpp"
#include "../Image/pack images.hpp"
#include "../Image/make image.hpp"
#include "../Image/write image.hpp"
#include "write atlas.hpp"
#include <fstream>

OptionsFileError::OptionsFileError(int line, int col, const char *what)
  : std::runtime_error("Options file error at line " + std::to_string(line) +
    " column " + std::to_string(col) + ": " + what) {}

#define CHECK_NODE(varName, node, strName, type)                                \
  const YAML::Node &varName = node;                                             \
  if (!varName) {                                                               \
    const YAML::Mark mark = varName.Mark();                                     \
    throw OptionsFileError(mark.line, mark.column,                              \
      "The \"" strName "\" property is missing");                               \
  } else if (varName.Type() != YAML::NodeType::type) {                          \
    const YAML::Mark mark = varName.Mark();                                     \
    throw OptionsFileError(mark.line, mark.column,                              \
      "The \"" strName "\" property is of the wrong type. Should be " #type);   \
  }

/*
max texture size: 65536 # if this is absent there is no limit
size:
  points: 32
  dpi:
    hori: 128
    vert: 128
ranges:
  -
    first: 32
    last: 126

*/

Font::Size getSize(const YAML::Node &doc) {
  const YAML::Node size = doc["size"];
    const YAML::Node points = size["points"];
    const YAML::Node dpi = size["dpi"];
      const YAML::Node horiDpi = dpi["hori"];
      const YAML::Node vertDpi = dpi["vert"];
  
  return {
    points.as<int>(),
    {
      horiDpi.as<int>(),
      vertDpi.as<int>()
    }
  };
}

/*unsigned getMaxTexSize(const YAML::Node &doc) {
  unsigned maxTexSize = std::numeric_limits<unsigned>::max();
  if (const YAML::Node node = doc["max texture size"]) {
    maxTexSize = node.as<unsigned>();
    if (!isPowerOf2(maxTexSize)) {
      const YAML::Mark mark = node.Mark();
      throw OptionsFileError(mark.line, mark.column,
        "\"max texture size\" must be a power of two");
    }
  }
  return maxTexSize;
}*/

std::vector<Glyphs> loadGlyphRanges(const YAML::Node &doc, const Font &font) {
  const YAML::Node ranges = doc["ranges"];
  std::vector<Glyphs> glyphs;
  
  for (auto r = ranges.begin(); r != ranges.end(); r++) {
    const uint32_t begin = (*r)["first"].as<uint32_t>();
    const uint32_t end = (*r)["last"].as<uint32_t>() + 1;
    glyphs.push_back(loadGlyphs(font, begin, end));
  }
  
  return glyphs;
}

void createAtlasFromOptionsFile(
  const std::string &optionsPath,
  const std::string &input,
  const std::string &output) {
  std::cout << "Reading options file \"" << optionsPath << "\"\n";
  
  std::ifstream file(optionsPath);
  const YAML::Node doc = YAML::Load(file);
  
  const Font font = loadFont(input, getSize(doc));
  //const unsigned maxTexSize = getMaxTexSize(doc);
  std::vector<Glyphs> glyphs = loadGlyphRanges(doc, font);
  std::vector<std::string> texPaths;
  std::vector<unsigned> texSizes;
  
  for (size_t i = 0; i != glyphs.size(); i++) {
    texPaths.push_back(output + "_" + std::to_string(i) + ".png");
    texSizes.push_back(packImages(glyphs[i].images));
    writeImage(
      texPaths.back(),
      makeImage(
        glyphs[i].images,
        texSizes.back()
      )
    );
  }
  
  writeAtlas(output + ".atlas", font, glyphs, texPaths, texSizes);
}

#undef CHECK_NODE
