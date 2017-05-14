//
//  caption.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "caption.hpp"

void UI::Caption::setFont(const std::string &newFont) {
  assert(newFont.size());
  font = newFont;
}

void UI::Caption::setText(const std::string &newText) {
  text = newText;
}

void UI::Caption::setFontSize(FontSize newFontSize) {
  fontSize = newFontSize;
}

const std::string &UI::Caption::getFont() const {
  return font;
}

const std::string &UI::Caption::getText() const {
  return text;
}

UI::FontSize UI::Caption::getFontSize() const {
  return fontSize;
}
