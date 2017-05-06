//
//  pack images.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef image_pack_images_hpp
#define image_pack_images_hpp

#include <vector>
#include "image.hpp"
#include "length.hpp"

class ImagePackError final : public std::runtime_error {
public:
  ImagePackError(const std::string &);
};

Length packImages(std::vector<Image> &);

#endif
