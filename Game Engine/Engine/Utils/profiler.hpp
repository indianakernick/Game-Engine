//
//  profiler.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_profiler_hpp
#define engine_utils_profiler_hpp

#include <chrono>
#include <unordered_map>
#include <iostream>
#include "../Math/siconstants.hpp"

class Profiler {
public:
  Profiler(const char *name);
  ~Profiler();
  
  static void formatInfo(std::ostream &);
  static void resetInfo();
private:
  struct TreeNode {
    uint64_t calls = 0;
    uint64_t time = 0;
    std::unordered_map<const char *, TreeNode> children;
    const char *name;
    TreeNode *parent;
  };
  
  std::chrono::high_resolution_clock::time_point start;
  static TreeNode *current;
  static TreeNode tree;
  
  static void recFormatInfo(std::ostream &, TreeNode *, int depth);
  
  static const int NAME_INDENT = 2;
  
  static const int PADDING_SIZE[6];
  enum PaddingType {
    NAME,
    COUNT,
    COUNT_PARENT,
    TIME,
    AVG_TIME,
    PERCENT
  };
  
  template <typename T>
  static void writeWithPadding(std::ostream &stream, PaddingType type, T anything) {
    size_t preWidth = stream.width();
    stream.width(PADDING_SIZE[type]);
    stream << std::left << anything;
    stream.width(preWidth);
  }
};

#endif
