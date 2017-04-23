//
//  main.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "search dir.hpp"
#include "load images.hpp"
#include "pack images.hpp"
#include "write atlas.hpp"
#include "make image.hpp"
#include "write image.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
  const std::vector<std::string> args(argv, argv + argc);
  
  const std::string workingDir = args[0].substr(0, args[0].find_last_of('/'));
  const std::string outputFile = args.size() > 1 ? args[1] : "output";
  
  try {
    std::vector<Image> images = loadImages(findFiles(workingDir));
    const int length = packImages(images);
    writeAtlas(outputFile + ".atlas", images, length);
    writeImage(outputFile + ".png", makeImage(images, length));
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
