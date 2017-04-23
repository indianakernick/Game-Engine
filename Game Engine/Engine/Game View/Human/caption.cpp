//
//  caption.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "caption.hpp"

const std::string UI::Caption::EMPTY_STRING = "";

void UI::Caption::setFont(const std::string &newFont) {
  assert(newFont.size());
  font = newFont;
}

void UI::Caption::setText(const std::string &newText) {
  text = newText;
}

const std::string &UI::Caption::getFont() const {
  return font;
}

const std::string &UI::Caption::getText() const {
  return text;
}

const std::string &UI::Caption::getTexture() const {
  return EMPTY_STRING;
}
