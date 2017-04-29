//
//  paragraph.cpp
//  Game Engine
//
//  Created by Indi Kernick on 27/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "paragraph.hpp"

const std::string UI::Paragraph::EMPTY_STRING = "";

void UI::Paragraph::setFont(const std::string &newFont) {
  assert(newFont.size());
  font = newFont;
}

void UI::Paragraph::setText(const std::string &newText) {
  text = newText;
}

void UI::Paragraph::setAlign(Align newAlign) {
  align = newAlign;
}

const std::string &UI::Paragraph::getFont() const {
  return font;
}

const std::string &UI::Paragraph::getText() const {
  return text;
}

UI::Paragraph::Align UI::Paragraph::getAlign() const {
  return align;
}

const std::string &UI::Paragraph::getTexture() const {
  return EMPTY_STRING;
}
