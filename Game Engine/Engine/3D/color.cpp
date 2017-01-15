//
//  color.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "color.hpp"

Color4F::Color4F(float r, float g, float b, float a)
  : r(r), g(g), b(b), a(a) {}

Color4F::Color4F(double r, double g, double b, double a)
  : r(r), g(g), b(b), a(a) {}

Color4F::Color4F(int r, int g, int b, int a)
  : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

bool Color4F::operator==(const Color4F &other) const {
  return r == other.r &&
         g == other.g &&
         b == other.b &&
         a == other.a;
}

bool Color4F::operator!=(const Color4F &other) const {
  return r != other.r ||
         g != other.g ||
         b != other.b ||
         a != other.a;
}

float &Color4F::operator[](int i) {
  assert(0 <= i && i < 4);
  return (&r)[i];
}

const float &Color4F::operator[](int i) const {
  assert(0 <= i && i < 4);
  return (&r)[i];
}

Color3F Color4F::to3F() const {
  return {r, g, b};
}

void Color4F::clamp() {
  r = Math::clamp(r, 0.0f, 1.0f);
  g = Math::clamp(g, 0.0f, 1.0f);
  b = Math::clamp(b, 0.0f, 1.0f);
  a = Math::clamp(a, 0.0f, 1.0f);
}

Color3F::Color3F(float r, float g, float b)
  : r(r), g(g), b(b) {}

Color3F::Color3F(double r, double g, double b)
  : r(r), g(g), b(b) {}

Color3F::Color3F(int r, int g, int b)
  : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f) {}

bool Color3F::operator==(const Color3F &other) const {
  return r == other.r &&
         g == other.g &&
         b == other.b;
}

bool Color3F::operator!=(const Color3F &other) const {
  return r != other.r ||
         g != other.g ||
         b != other.b;
}

float &Color3F::operator[](int i) {
  assert(0 <= i && i < 3);
  return (&r)[i];
}

const float &Color3F::operator[](int i) const {
  assert(0 <= i && i < 3);
  return (&r)[i];
}

Color4F Color3F::to4F() const {
  return {r, g, b};
}

void Color3F::clamp() {
  r = Math::clamp(r, 0.0f, 1.0f);
  g = Math::clamp(g, 0.0f, 1.0f);
  b = Math::clamp(b, 0.0f, 1.0f);
}
