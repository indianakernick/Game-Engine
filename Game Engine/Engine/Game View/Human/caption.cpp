//
//  caption.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "caption.hpp"

const Res::ID UI::Caption::NULL_RES_ID = {};

void UI::Caption::setFont(const Res::ID &newFont) {
  assert(newFont);
  font = newFont;
}

void UI::Caption::setText(const std::string &newText) {
  text = newText;
}

const Res::ID &UI::Caption::getFont() const {
  return font;
}

const std::string &UI::Caption::getText() const {
  return text;
}

const Res::ID &UI::Caption::getTexture() const {
  return NULL_RES_ID;
}
