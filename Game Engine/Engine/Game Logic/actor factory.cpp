//
//  actor factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "actor factory.hpp"

void ActorFactory::addCreator(const std::string &name, ComponentCreator creator) {
  bool inserted = creators.emplace(name, creator).second;
  if (!inserted) {
    throw std::runtime_error("Duplicate creator");
  }
}

ActorPtr ActorFactory::createActor(std::string xmlFile) {
  ActorPtr actor(new Actor(idGen.create()));
  
  std::ifstream file(Resource::path() + xmlFile);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }
  XML::NodePtr node = XML::Node::read(file);
  XML::Children &components = node->getChildren();
  
  for (auto i = components.begin(); i != components.end(); i++) {
    ComponentPtr comp = createComponent(*i);
    actor->addComponent(comp);
    comp->setActor(actor);
  }
  
  return actor;
}

ComponentPtr ActorFactory::createComponent(XML::NodePtr node) {
  ComponentPtr comp;
  
  auto iter = creators.find(node->getName());
  if (iter != creators.end()) {
    comp.reset(iter->second());
  } else {
    throw std::runtime_error("Failed to find creator");
  }
  
  comp->init(node);
  
  return comp;
}
