//
//  line col.cpp
//  Game Engine
//
//  Created by Indi Kernick on 25/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "line col.hpp"

Res::LineCol::LineCol(LineType line, ColType col)
  : line(line), col(col) {
  assert(line >= FIRST_LINE);
  assert(col >= FIRST_COL);
}

void Res::LineCol::update(char c) {
  switch (c) {
    case '\t':
      col += SIZE_OF_TAB;
      break;
    case '\n':
      line++;
      col = FIRST_COL;
      break;
    case '\v':
    case '\f':
      line++;
      break;
    case '\r':
      col = FIRST_COL;
      break;
    case '\b':
      //backspace doesn't move up lines
      //when backspacing tabs it treats them as spaces so it only
      //moves back one char
      if (col != FIRST_COL) {
        col--;
      }
    case '\0':
    case EOF:
      break;
    
    default:
      if (std::isprint(c)) {
        col++;
      }
  }
}

void Res::LineCol::update(const char *str) {
  assert(str);
  while (*str) {
    update(*str);
    str++;
  }
}

void Res::LineCol::update(const char *str, size_t size) {
  assert(str);
  while (size) {
    update(*str);
    str++;
    size--;
  }
}

void Res::LineCol::reset() {
  line = FIRST_LINE;
  col = FIRST_COL;
}

Res::LineCol::LineType Res::LineCol::getLine() const {
  return line;
}

Res::LineCol::ColType Res::LineCol::getCol() const {
  return col;
}

const char *Res::LineCol::getStr() const {
  //The largest 64 bit integer value is 18446744073709551615 which is
  //20 characters. 20 + 20 + ':' + '\0' = 42
  static char str[42];
  snprintf(str, 42, "%u:%u", line, col);
  return str;
}
