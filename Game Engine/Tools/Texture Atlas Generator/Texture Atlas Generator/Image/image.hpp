//
//  image.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

#include <memory>
#include <string>
#include "vector.hpp"

class Image {
public:
  using Data = std::unique_ptr<uint8_t, void (*)(void *)>;
  
  enum Format {
    GREY = 1,
    GREY_ALPHA = 2,
    RGB = 3,
    RGB_ALPHA = 4
  };
  
  Image();
  Image(int, int, Format);
  Image(int, int, Format, uint8_t *, void (*)(void *));
  Image(int, int, Format, uint8_t *, const std::string &);
  
  Data data;
  std::string path;
  ivec2 p;
  ivec2 s;
  Format format = Format::RGB_ALPHA;
};

#endif
