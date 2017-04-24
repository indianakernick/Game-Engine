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
#include "image.hpp"

class AtlasWriteError final : public std::runtime_error {
public:
  AtlasWriteError(const std::string &, const std::string &);
};

void writeAtlas(const std::string &, const std::vector<Image> &, int);

#endif