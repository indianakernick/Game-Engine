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
#include "../Serial/xml.hpp"

class Actor;
using ActorPtr = std::shared_ptr<Actor>;

class Component {
friend class ActorFactory;
friend class Actor;
public:
  using ID = uint8_t;

  Component() = default;
  virtual ~Component() = default;
  
  virtual void init(XML::NodePtr) = 0;
  
  virtual ID getID() const = 0;
  virtual void update(double) = 0;
  
protected:
  ActorPtr actor;
  
  void broadcastMessage(int id, void *data = nullptr);
  void sendMessage(Component::ID to, int id, void *data = nullptr);
  
  virtual void onMessage(Component::ID from, int id, void *data) = 0;
private:
  void setActor(ActorPtr);
};

using ComponentPtr = std::shared_ptr<Component>;

#include "actor.hpp"

#endif
