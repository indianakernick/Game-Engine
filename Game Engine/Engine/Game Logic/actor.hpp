//
//  actor.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_actor_hpp
#define engine_game_logic_actor_hpp

#include <map>
#include <memory>
#include "component.hpp"
#include "../ID/interface.hpp"
#include <type_traits>
#include <queue>

class Actor {
friend class ActorFactory;
friend class Component;
public:
  using ID = ID::Type;
  
  Actor(ID);
  ~Actor() = default;
  
  void init(XML::NodePtr);
  ///Components hold strong references to Actors so this function
  ///breaks the circulur reference
  void destroy();
  
  //T has to be derived from Component
  template<typename T>
  std::enable_if<std::is_base_of<Component, T>::VALUE, std::weak_ptr<T>> getComponent() {
    Component::ID id = T::COMP_ID;
    auto iter = components.find(id);
    if (iter != components.end()) {
      return std::dynamic_pointer_cast<T>(iter->second);
    } else {
      throw std::runtime_error("No component with that ID was found");
    }
  }
  
  ID getID() const;
  
  void update(double delta);
private:
  ID id;
  
  using Components = std::map<Component::ID, ComponentPtr>;
  Components components;
  void addComponent(ComponentPtr);
  
  static const Component::ID ALL_COMPONENTS;
  struct Message {
    Message(Component::ID, Component::ID, int id, void *data);
  
    Component::ID from;
    Component::ID to;
    int id;
    void *data;
  };
  std::queue<Message> messageQueue;
  void flushMessages();
};

using ActorPtr = std::shared_ptr<Actor>;

#endif
