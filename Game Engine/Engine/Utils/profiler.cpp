//
//  profiler.cpp
//  game engine
//
//  Created by Indi Kernick on 12/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "profiler.hpp"

Profiler::TreeNode Profiler::tree;
Profiler::TreeNode *Profiler::current = &tree;
const int Profiler::PADDING_SIZE[6] = {48, 16, 24, 20, 20, 24};

Profiler::Profiler(const char *name) {
  TreeNode *prevCurrent = current;
  current = &current->children[name];
  current->parent = prevCurrent;
  current->name = name;
  start = std::chrono::high_resolution_clock::now();
}

Profiler::~Profiler() {
  TimePoint end = std::chrono::high_resolution_clock::now();
  uint64_t time = end.time_since_epoch().count() - start.time_since_epoch().count();
  current->calls++;
  current->time += time;
  current = current->parent;
}

void Profiler::formatInfo(std::ostream &stream) {
  stream << "Name                                            "
            "Total Count     "
            "Avg Count per parent    "
            "Total Time (ms)     "
            "Average Time (ms)   "
            "Percent of parent time  "
            "\n";
  tree.name = "ROOT";
  std::streamsize oldPrec = stream.precision();
  stream.precision(3);
  recFormatInfo(stream, &tree, 0);
  stream.precision(oldPrec);
}

void Profiler::resetInfo() {
  current = nullptr;
  tree.calls = 0;
  tree.time = 0;
  tree.children.clear();
  tree.parent = nullptr;
}

void Profiler::recFormatInfo(std::ostream &stream, TreeNode *node, int depth) {
  int newDepth;
  if (node->parent) {
    newDepth = depth + 1;

    std::string name;
    for (int i = 0; i < depth; ++i) {
      name += "  ";
    }
    name += node->name;
    stream.width(48);
    stream << std::left << name;

    stream.width(16);
    stream << std::left << node->calls;
    
    stream.width(24);
    //not child of root
    if (node->parent->parent) {
      stream << std::left << node->calls / node->parent->calls;
    } else {
      stream << std::left << node->calls;
    }

    stream.width(20);//         convert nanoseconds to milliseconds
    stream << std::left << (static_cast<double>(node->time) / 1'000'000);

    stream.width(20);
    if (node->calls) {
      stream << std::left << ((static_cast<double>(node->time) / node->calls) / 1'000'000);
    } else {
      stream << std::left << 0;
    }
    
    //not child of root
    if (node->parent->parent) {
      stream << ((static_cast<double>(node->time) / node->parent->time) * 100) << "%";
    }
    stream << '\n';
  } else {
    newDepth = 0;
  }
  for (auto i = node->children.begin(); i != node->children.end(); ++i) {
    recFormatInfo(stream, &(i->second), newDepth);
  }
}