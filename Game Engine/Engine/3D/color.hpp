//
//  color.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_color_hpp
#define engine_3d_color_hpp

#include "../Math/clamp.hpp"
#include <cassert>

#pragma pack(1)

class Color3F;

class Color4F {
public:
  Color4F() = default;
  Color4F(float r, float g, float b, float a = 1.0f);
  Color4F(double r, double g, double b, double a = 1.0);
  Color4F(int r, int g, int b, int a = 255);
  
  bool operator==(const Color4F &) const;
  bool operator!=(const Color4F &) const;
  
  float &operator[](int);
  const float &operator[](int) const;
  
  Color3F to3F() const;
  
  void clamp();
  
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 0.0f;
};

class Color3F {
public:
  Color3F() = default;
  Color3F(float r, float g, float b);
  Color3F(double r, double g, double b);
  Color3F(int r, int g, int b);
  
  bool operator==(const Color3F &) const;
  bool operator!=(const Color3F &) const;
  
  float &operator[](int);
  const float &operator[](int) const;
  
  Color4F to4F() const;
  
  void clamp();
  
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
};

#pragma pack()

#endif
