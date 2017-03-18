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
#include "../Resource/Handles/xml.hpp"
#include "../Application/global resource cache.hpp"

namespace Game {
  class ActorFactory {
  private:
    using ComponentCreator = std::function<Component * ()>;
    using ComponentCreatorMap = std::map<std::string, ComponentCreator>;
  public:
    ActorFactory();
    
    void addCreator(const std::string &name, ComponentCreator creator);
    Actor::Ptr createActor(const Res::ID &xmlFile);

  private:
    ComponentCreatorMap creators;
    ID::Local<Actor::ID> idGen;
    
    Component::Ptr createComponent(const tinyxml2::XMLElement *);
  };
}

#endif
