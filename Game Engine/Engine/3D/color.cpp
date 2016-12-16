//
//  color.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "color.hpp"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
  : r(r), g(g), b(b), a(a) {}

Color::Color(float r, float g, float b, float a)
  : r(std::round(r * 255)),
    g(std::round(g * 255)),
    b(std::round(b * 255)),
    a(std::round(a * 255)) {}

Color::Color(uint32_t rgba) {
  *reinterpret_cast<uint32_t *>(&r) = rgba;
}

Color::Color(uint16_t rgba)
  //each component is 4 bits
  //so i copy the 4 bit component into
  //the upper half of the 8 bit component
  : r((rgba & 0xF000) >> 8),
    g((rgba & 0x0F00) >> 4),
    b((rgba & 0x00F0)),
    a(rgba << 4) {}

Color::Color(uint8_t rgba)
  : r(rgba & 0b11000000),
    g((rgba & 0b00110000) << 2),
    b((rgba & 0b00001100) << 4),
    a((rgba & 0b00000011) << 6) {}

std::array<float, 4> Color::rgbaFloat() {
  return {{r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f}};
}

uint32_t Color::rgba() {
  return rgba8();
}

uint32_t Color::rgba8() {
  return *reinterpret_cast<uint32_t *>(&r);
}

uint16_t Color::rgba4() {
  return ((r & 0xF0) << 8) |
         ((g & 0xF0) << 4) |
         (b & 0xF0) |
         (a >> 4);
}

uint8_t Color::rgba2() {
  return (r & 0b11000000) |
         ((g & 0b11000000) >> 2) |
         ((b & 0b11000000) >> 4) |
         ((a & 0b11000000) >> 8);
}
