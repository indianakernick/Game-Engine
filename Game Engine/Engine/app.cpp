//
//  app.cpp
//  electric sim
//
//  Created by Indi Kernick on 15/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "app.hpp"

/*TaskManager App::taskManager;
bool App::initialized = false;
std::unique_ptr<Graphics::Window> App::window;
std::unique_ptr<Loader::Assets> App::assetLoader;

void App::init(Graphics::Window::Info info, Uint32 sdlFlags, int imgFlags) {
  if (!initialized) {
    initialized = true;
    if (SDL_Init(sdlFlags) < 0) {
      std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    } else {
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "Failed to initialize SDL_IMG: " << IMG_GetError() << std::endl;
      }
      if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_TTF: " << TTF_GetError() << std::endl;
      }
      if (Mix_Init(MIX_INIT_MP3) == -1) {
        std::cerr << "Failed to initialize SDL_MIX: " << Mix_GetError() << std::endl;
      }
    }
    
    window = std::make_unique<Graphics::Window>(info);
    assetLoader = std::make_unique<Loader::Assets>(getRenderer());
  } else {
    std::cerr << "Tried to initalize app but it was already initalized" << std::endl;
  }
}

void App::quit() {
  if (initialized) {
    initialized = false;
    taskManager.quit();
    
    assetLoader.reset();
    window.reset();
    
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
  } else {
    std::cerr << "Tried to quit app but it wasn't initialized" << std::endl;
  }
}*/