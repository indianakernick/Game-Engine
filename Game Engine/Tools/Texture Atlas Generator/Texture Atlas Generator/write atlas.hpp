//
//  write atlas.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef write_atlas_hpp
#define write_atlas_hpp

#include <string>
#include <vector>
#include "Image/image.hpp"
#include "Font/glyph.hpp"
#include "Font/font.hpp"

class AtlasWriteError final : public std::runtime_error {
public:
  AtlasWriteError(const std::string &);
};

void writeAtlas(const std::string &, const std::vector<Image> &, int);
void writeAtlas(const std::string &, const Font &, const Glyphs &, int);

#endif
