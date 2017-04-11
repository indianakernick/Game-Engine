//
//  font.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "font.hpp"

const std::string &Res::FontLoader::getName() const {
  static const std::string NAME = "Font";
  return NAME;
}

bool Res::FontLoader::canLoad(std::experimental::string_view ext) const {
  return ext == "ttf";
}

Res::Handle::Ptr Res::FontLoader::load(const ID &id) const {
  assert(id.getData().is<NewFontInfo>());
  const NewFontInfo fontInfo = id.getData().as<NewFontInfo>();
  assert(fontInfo.numChars > 0);
  Platform::Font::Ptr font = Platform::loadFont(
    readFile(id),
    fontInfo.size,
    fontInfo.firstChar,
    fontInfo.numChars
  );
  Font::Ptr handle = std::make_shared<Font>(font);
  handle->addSize(font->getByteSize());
  return handle;
}
