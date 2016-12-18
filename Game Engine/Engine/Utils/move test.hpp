//
//  move test.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_move_test_hpp
#define engine_utils_move_test_hpp

#include <iostream>

class MoveTest {
public:
  MoveTest();
  MoveTest(const MoveTest &);
  MoveTest(MoveTest &&);
  
  virtual ~MoveTest();
  
  MoveTest &operator=(const MoveTest &);
  MoveTest &operator=(MoveTest &&);
  
  static MoveTest rValue();
  static MoveTest lValue;
  
  static void startLogging();
  static void stopLogging();
private:
  static bool logging;
};

template <typename T>
class MoveCounter {
public:
  struct Count {
    int defaultCtor = 0;
    int copyCtor = 0;
    int moveCtor = 0;
    int dtor = 0;
    int copyAssign = 0;
    int moveAssign = 0;
  };
  
  MoveCounter() {
    count.defaultCtor++;
  }
  MoveCounter(const MoveCounter &) {
    count.copyCtor++;
  }
  MoveCounter(MoveCounter &&) {
    count.moveCtor++;
  }
  
  virtual ~MoveCounter() {
    count.dtor++;
  }
  
  MoveCounter &operator=(const MoveCounter &) {
    count.copyAssign++;
  }
  MoveCounter &operator=(MoveCounter &&) {
    count.moveAssign++;
  }
  
  static const Count &getCount() {
    return count;
  }
  static void logCount() {
    std::cerr << "\nDefault constructor  " << count.defaultCtor
              << "\nCopy constructor     " << count.copyCtor
              << "\nMove constructor     " << count.moveCtor
              << "\nDestructor           " << count.dtor
              << "\nCopy assign          " << count.copyAssign
              << "\nMove assign          " << count.moveAssign
              << '\n'
              << '\n';
  }
  static void resetCount() {
    memset(&count, 0, sizeof(Count));
  }
  
private:
  static Count count;
};

template <typename T>
typename MoveCounter<T>::Count MoveCounter<T>::count;

#endif
