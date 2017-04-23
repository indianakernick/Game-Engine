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

struct Image {
  using Data = std::unique_ptr<uint8_t>;
  
  Image() = default;
  Image(int, int);
  Image(int, int, uint8_t *, const std::string &);
  
  Data data;
  std::string path;
  int x = 0, y = 0, w = 0, h = 0;
};

#endif
