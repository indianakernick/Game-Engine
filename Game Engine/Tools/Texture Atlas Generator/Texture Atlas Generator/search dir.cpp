//
//  search dir.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "search dir.hpp"

#include <experimental/string_view>
#include <dirent.h>
#include <iostream>

DirSearchError::DirSearchError()
  : std::runtime_error("Failed to search for files in this directory") {}

NoSupportedFilesError::NoSupportedFilesError()
  : std::runtime_error("There are no supported image files in this directory") {}

bool formatIsSupported(std::experimental::string_view ext) {
  static std::experimental::string_view EXTS[] = {
    "jpg", "jpeg", "png", "bmp", "psd", "tga", "gif", "hdr", "pic", "pgm", "ppm"
  };
  static const size_t EXTS_NUM = sizeof(EXTS) / sizeof(std::experimental::string_view);
  
  for (std::experimental::string_view *e = EXTS; e != EXTS + EXTS_NUM; e++) {
    if (ext == *e) {
      return true;
    }
  }
  return false;
}

std::vector<std::string> filterFiles(const std::vector<std::string> &files) {
  std::vector<std::string> newFiles;
  
  for (auto f = files.begin(); f != files.end(); f++) {
    std::experimental::string_view ext = f->c_str() + f->find_last_of('.') + 1;
    if (ext.size() == 0) {
      continue;
    }
    if (formatIsSupported(ext)) {
      newFiles.push_back(*f);
    }
  }
  
  if (newFiles.size() == 0) {
    throw NoSupportedFilesError();
  }
  
  return newFiles;
}

std::vector<std::string> findFiles(const std::string &path) {
  std::cout << "Searching directory \"" << path << "\" for image files\n";
  
  std::vector<std::string> files;
  
  std::unique_ptr<DIR, int(*)(DIR *)> dir(opendir("."), &closedir);
  if (dir) {
    while (dirent *ent = readdir(dir.get())) {
      files.push_back(ent->d_name);
    }
  } else {
    throw DirSearchError();
  }
  
  return filterFiles(files);
}
