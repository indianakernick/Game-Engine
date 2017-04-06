//
//  texture.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture.hpp"

const std::string &Res::TextureLoader::getName() const {
  static const std::string NAME = "Texture";
  return NAME;
}

bool Res::TextureLoader::canLoad(std::experimental::string_view ext) const {
  static const char *EXTS[] = {
    "jpg","jpeg","png","bmp","psd","tga","gif","hdr","pic","pgm","ppm"
  };
  return hasExt(EXTS, ext);
}

Res::Handle::Ptr Res::TextureLoader::load(const ID &id) const {
  const Any &data = id.getData();
  Graphics3D::TexParams params;
  if (data.is<Graphics3D::TexParams>()) {
    params = data.as<Graphics3D::TexParams>();
  }

  int width, height, format = params.hasAlpha ? STBI_rgb_alpha : STBI_rgb;
  Byte *pixels = stbi_load_from_file(openFile(id).get(),
                                     &width, &height,
                                     nullptr, format);
  
  Memory::Buffer buf(pixels, width * height * format, Memory::ALIAS);
  Platform::Texture::Ptr texture =
    Platform::makeTexture(buf, {width, height}, params);
  stbi_image_free(pixels);
  return std::make_shared<Texture>(texture);
}
