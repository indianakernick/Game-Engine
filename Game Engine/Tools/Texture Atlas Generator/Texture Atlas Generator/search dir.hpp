//
//  search dir.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef search_dir_hpp
#define search_dir_hpp

#include <vector>
#include <string>

class DirSearchError final : public std::runtime_error {
public:
  DirSearchError();
};

class NoSupportedFilesError final : public std::runtime_error {
public:
  NoSupportedFilesError();
};

std::vector<std::string> findFiles(const std::string &);

#endif
