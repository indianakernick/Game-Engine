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
#include <cassert>
#include "../Game Logic/actor.hpp"

namespace Game {
  class View {
  public:
    using Ptr = std::shared_ptr<View>;
    using ID = uint8_t;

    enum Type {
      HUMAN,
      AI
    };

    View() = default;
    virtual ~View() = default;
    
    virtual void init() = 0;
    virtual void update(uint64_t) = 0;
    virtual void render() {}
    virtual void quit() = 0;
    virtual Type getType() = 0;
    virtual void onAttach();
    virtual void onDetach();
    
    void attach(View::ID, Actor::ID);
    void detach();
    
    View::ID getID() const;
    Actor::ID getActor() const;
    bool isAttached() const;
  private:
    View::ID id = 0;
    Actor::ID actor = 0;
    bool attached = false;
  };
}

#endif
