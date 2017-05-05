//
//  pack images.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef pack_images_hpp
#define pack_images_hpp

#include <vector>
#include "image.hpp"

class ImagePackError final : public std::runtime_error {
public:
  ImagePackError(const std::string &);
};

unsigned calcArea(const std::vector<Image> &);
unsigned calcLength(unsigned);
void packImages(std::vector<Image> &, unsigned);
unsigned packImages(std::vector<Image> &);

#endif
