//
//  profiler.hpp
//  game engine
//
//  Created by Indi Kernick on 12/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef profiler_hpp
#define profiler_hpp

#include <chrono>
#include <unordered_map>
#include <iostream>

class Profiler {
public:
  Profiler(const char *name);
  ~Profiler();
  
  static void formatInfo(std::ostream &);
  static void resetInfo();
private:
  using TimePoint = std::chrono::high_resolution_clock::time_point;

  struct TreeNode {
    uint64_t calls = 0;
    uint64_t time = 0;
    std::unordered_map<const char *, TreeNode> children;
    const char *name;
    TreeNode *parent;
  };
  
  TimePoint start;
  static TreeNode *current;
  static TreeNode tree;
  
  static void recFormatInfo(std::ostream &, TreeNode *, int depth);
  
  static const int PADDING_SIZE[6];
  template <typename T>
  void writeWithPadding(std::ostream &stream, int paddingIndex, T &anything) {
    size_t preWidth = stream.width();
    stream.width(PADDING_SIZE[paddingIndex]);
    stream << std::left << anything;
    stream.width(preWidth);
  }
};

#endif