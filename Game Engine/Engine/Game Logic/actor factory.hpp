//
//  actor factory.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_actor_factory_hpp
#define engine_game_logic_actor_factory_hpp

#include <map>
#include <string>
#include <functional>
#include "actor.hpp"
#include "../ID/local.hpp"
#include "../Resource/Managers/xml.hpp"

namespace Game {
  using ComponentCreator = std::function<Component::Ptr ()>;
  
  class DuplicateCreator final : public std::runtime_error {
  public:
    DuplicateCreator();
  };
  
  class MissingCreator final : public std::runtime_error {
  public:
    MissingCreator();
  };
  
  class ActorFactory {
  public:
    ActorFactory();
    ~ActorFactory() = default;
    
    void addCreator(const std::string &, const ComponentCreator &);
    Actor::Ptr createActor(const std::string &);

  private:
    using ComponentCreatorMap = std::map<std::string, ComponentCreator>;
    ComponentCreatorMap creators;
    ID::Local<Actor::ID> idGen;
    
    Component::Ptr createComponent(const tinyxml2::XMLElement *);
  };
}

#endif
