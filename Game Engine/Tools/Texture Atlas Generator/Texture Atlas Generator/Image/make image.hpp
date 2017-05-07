//
//  make image.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef image_make_image_hpp
#define image_make_image_hpp

#include "image.hpp"
#include <vector>
#include "length.hpp"

class FormatError : public std::runtime_error {
public:
  FormatError();
};

Image makeImage(const std::vector<Image> &, Length);

#endif
