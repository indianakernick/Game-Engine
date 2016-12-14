//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_base_hpp
#define engine_game_view_base_hpp

#include <memory>
#include "../ID/rand.hpp"
#include "../Input/event.hpp"

class GameView {
public:
  using Ptr = std::shared_ptr<GameView>;

  GameView() = default;
  virtual ~GameView() = default;
  
  virtual void init() = 0;
  virtual void update(uint64_t) = 0;
  virtual void render() {};
  virtual bool onInput(Input::Event::Ptr) = 0;
};

#endif
