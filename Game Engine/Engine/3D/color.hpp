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
  IColor() = default;
  IColor(int r, int g, int b, int a = 255);
  IColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  IColor(float r, float g, float b, float a = 1.0);
  explicit IColor(const FColor &);
  explicit IColor(uint32_t);
  explicit IColor(uint16_t);
  explicit IColor(uint8_t);
  
  bool operator==(IColor) const;
  bool operator!=(IColor) const;
  
  FColor rgbaFloat();
  
  uint16_t rgba4();
  uint8_t rgba2();
  
  union {
    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
    };
    uint32_t rgba = 0;
  };
};

class FColor {
public:
  FColor() = default;
  FColor(float r, float g, float b, float a = 1.0f);
  FColor(int r, int g, int b, int a = 255);
  FColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  explicit FColor(IColor);
  
  bool operator==(const FColor &) const;
  bool operator!=(const FColor &) const;
  
  IColor rgbaInt();
  
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 0.0f;
};

#pragma pack()

#endif
