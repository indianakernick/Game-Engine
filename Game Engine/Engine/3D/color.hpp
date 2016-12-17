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

class FColor;

#pragma pack(1)

class IColor {
public:
  IColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  IColor(float r, float g, float b, float a = 1.0);
  IColor(const FColor &);
  explicit IColor(uint32_t);
  explicit IColor(uint16_t);
  explicit IColor(uint8_t);
  
  bool operator==(IColor) const;
  bool operator!=(IColor) const;
  
  FColor rgbaFloat();
  
  uint32_t rgba();
  uint32_t rgba8();
  uint16_t rgba4();
  uint8_t rgba2();
  
  uint8_t r, g, b, a;
};

class FColor {
public:
  FColor(float r, float g, float b, float a = 1.0f);
  FColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  FColor(IColor);
  
  bool operator==(const FColor &) const;
  bool operator!=(const FColor &) const;
  
  IColor rgbaInt();
  
  float r, g, b, a;
};

#pragma pack()

#endif
