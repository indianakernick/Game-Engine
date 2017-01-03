//
//  component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_component_hpp
#define engine_game_logic_component_hpp

#include <memory>
#include "../../Libraries/tinyxml2.hpp"

namespace Game {
  class Actor;

  class Component {
  friend class ActorFactory;
  friend class Actor;
  public:
    using Ptr = std::shared_ptr<Component>;
    using ID = uint8_t;

    Component() = default;
    virtual ~Component() = default;
    
    virtual void init(const tinyxml2::XMLElement *) = 0;
    
    virtual ID getID() const = 0;
    virtual void update(uint64_t) = 0;
    
  protected:
    Actor *actor = nullptr;
    
    void broadcastMessage(int id, void *data = nullptr);
    void sendMessage(Component::ID to, int id, void *data = nullptr);
    
    virtual void onMessage(Component::ID from, int id, void *data) = 0;
  };
}

#include "actor.hpp"

#endif
