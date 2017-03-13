//
//  main.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "Engine/Application/impl.hpp"

int main(int, char const**) {
  app = new Game::AppImpl;
  app->mainloop();
  delete app;
  PROFILER_INFO(std::cout);
  
  return EXIT_SUCCESS;
}
