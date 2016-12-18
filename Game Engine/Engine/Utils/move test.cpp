//
//  move test.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "move test.hpp"

MoveTest MoveTest::lValue;
bool MoveTest::logging = false;

MoveTest::MoveTest() {
  if (logging) {
    std::cerr << "Default constructor\n";
  }
}

MoveTest::MoveTest(const MoveTest &) {
  if (logging) {
    std::cerr << "Copy constructor\n";
  }
}

MoveTest::MoveTest(MoveTest &&) {
  if (logging) {
    std::cerr << "Move constructor\n";
  }
}

MoveTest::~MoveTest() {
  if (logging) {
    std::cerr << "Destructor\n";
  }
}

MoveTest &MoveTest::operator=(const MoveTest &) {
  if (logging) {
    std::cerr << "Copy assignment\n";
  }
  return *this;
}

MoveTest &MoveTest::operator=(MoveTest &&) {
  if (logging) {
    std::cerr << "Move assignment\n";
  }
  return *this;
}

MoveTest MoveTest::rValue() {
  return {};
}

void MoveTest::startLogging() {
  logging = true;
}

void MoveTest::stopLogging() {
  logging = false;
}
