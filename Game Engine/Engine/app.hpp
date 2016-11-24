//
//  app.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef app_hpp
#define app_hpp

/*class App {
public:
  App() = delete;
  static void init(Graphics::Window::Info info,
                   Uint32 sdlFlags = SDL_INIT_EVERYTHING,
                   int imgFlags = IMG_INIT_JPG |
                                  IMG_INIT_PNG |
                                  IMG_INIT_TIF |
                                  IMG_INIT_WEBP);
  static void quit();
  
  static inline TaskManager &getTaskManager() {
    return taskManager;
  }
  static inline Graphics::Renderer &getRenderer() {
    return window->getRenderer();
  }
  static inline Loader::Assets &getAssetLoader() {
    return *assetLoader;
  }
  
  static inline uint64_t getTimeNano() {
    using namespace std::chrono;
    high_resolution_clock::time_point now = high_resolution_clock::now();
    return now.time_since_epoch().count();
  }
  static inline double getTimeSec() {
    using namespace std::chrono;
    high_resolution_clock::time_point now = high_resolution_clock::now();
    return static_cast<double>(now.time_since_epoch().count()) / 1'000'000'000;
  }
private:
  static bool initialized;
  static TaskManager taskManager;
  static std::unique_ptr<Loader::Assets> assetLoader;
};*/

#endif
