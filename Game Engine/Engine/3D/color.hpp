//
//  color.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_color_hpp
#define engine_3d_color_hpp

#include <cstdint>
#include <cmath>
#include <array>

#pragma pack(1)
class Color {
public:
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  Color(float r, float g, float b, float a = 1.0);
  explicit Color(uint32_t);
  explicit Color(uint16_t);
  explicit Color(uint8_t);
  
  std::array<float, 4> rgbaFloat();
  
  uint32_t rgba();
  uint32_t rgba8();
  uint16_t rgba4();
  uint8_t rgba2();
  
  uint8_t r, g, b, a;
};
#pragma pack()

#endif
