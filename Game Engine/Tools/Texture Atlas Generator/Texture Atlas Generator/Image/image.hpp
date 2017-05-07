//
//  image.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef image_image_hpp
#define image_image_hpp

#include <memory>
#include <string>
#include "../vector.hpp"

class Image {
public:
  using Deleter = void (*)(void *);
  using Data = std::unique_ptr<uint8_t, Deleter>;
  
  enum Format : unsigned {
    GREY       = 1,
    GREY_ALPHA = 2,
    RGB        = 3,
    RGB_ALPHA  = 4
  };
  
  Image() = delete;
  Image(unsigned, unsigned, Format);
  Image(unsigned, unsigned, Format, uint8_t *, Deleter, const std::string & = "");
  
  Data data;
  std::string path;
  uivec2 p;
  uivec2 s;
  Format format = Format::RGB_ALPHA;
};

#endif
