//
//  profiler.cpp
//  Game Engine
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
  current->time += (std::chrono::high_resolution_clock::now() - start).count();
  ++current->calls;
  current = current->parent;
}

void Profiler::formatInfo(std::ostream &stream) {
  writeWithPadding(stream, NAME,         "Name");
  writeWithPadding(stream, COUNT,        "Total Count");
  writeWithPadding(stream, COUNT_PARENT, "Avg Count per parent");
  writeWithPadding(stream, TIME,         "Total Time (ms)");
  writeWithPadding(stream, AVG_TIME,     "Average Time (ms)");
  writeWithPadding(stream, PERCENT,      "Percent of parent time");
  stream << '\n';
  
  tree.name = "ROOT";
  std::streamsize oldPrec = stream.precision();
  stream.precision(NUM_PRECISION);
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

    writeWithPadding(stream, NAME,
      std::string(depth * NAME_INDENT, ' ') + node->name);
    
    writeWithPadding(stream, COUNT, node->calls);
    
    //not child of root
    if (node->parent->parent) {
      writeWithPadding(stream, COUNT_PARENT, node->calls / node->parent->calls);
    } else {
      writeWithPadding(stream, COUNT_PARENT, node->calls);
    }

    writeWithPadding(stream, TIME, node->time * Math::SI::NANO_MILLI);

    if (node->calls) {
      writeWithPadding(stream, AVG_TIME, (node->time * Math::SI::NANO_MILLI) / node->calls);
    } else {
      writeWithPadding(stream, AVG_TIME, 0);
    }
    
    //not child of root
    if (node->parent->parent) {
      writeWithPadding(stream, PERCENT, ((static_cast<double>(node->time) / node->parent->time) * 100));
      stream << '%';
    }
    stream << '\n';
  } else {
    newDepth = 0;
  }
  
  //copy children into a vector
  std::vector<TreeNode *> children;
  children.reserve(node->children.size());
  for (auto i = node->children.begin(); i != node->children.end(); ++i) {
    children.push_back(&(i->second));
  }
  
  //sort by total time in accending order
  std::sort(children.begin(), children.end(), [](TreeNode *a, TreeNode *b) {
    return a->time > b->time;
  });
  
  for (auto i = children.begin(); i != children.end(); ++i) {
    recFormatInfo(stream, *i, newDepth);
  }
}
