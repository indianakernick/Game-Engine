//
//  actor factory.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef actor_factory_hpp
#define actor_factory_hpp

#include <map>
#include <string>
#include <functional>
#include "actor.hpp"
#include "../ID/count.hpp"
#include "../Resource/path.hpp"

class ActorFactory {
private:
  using ComponentCreator = std::function<Component * ()>;
  using ComponentCreatorMap = std::map<std::string, ComponentCreator>;
public:
  ActorFactory() = default;
  
  void addCreator(const std::string &name, ComponentCreator creator);
  ActorPtr createActor(std::string xmlFile);

private:
  ComponentCreatorMap creators;
  ID::Count idGen;
  
  ComponentPtr createComponent(XML::NodePtr);
};

#endif