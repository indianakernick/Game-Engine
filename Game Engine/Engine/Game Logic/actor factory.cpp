//
//  actor factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "actor factory.hpp"

Game::ActorFactory::ActorFactory() {
  idGen.reserve(Actor::NULL_ID);
}

void Game::ActorFactory::addCreator(const std::string &name, ComponentCreator creator) {
  bool inserted = creators.emplace(name, creator).second;
  if (!inserted) {
    throw std::runtime_error("Duplicate creator");
  }
}

Game::Actor::Ptr Game::ActorFactory::createActor(Resource::Handle::Ptr xmlFile) {
  Actor::Ptr actor(new Actor(idGen.create()));
  
  Resource::Descs::XML::Ptr desc = xmlFile->getDesc<Resource::Descs::XML>();
  const tinyxml2::XMLElement &root = desc->getRoot();
  
  for (const tinyxml2::XMLElement *i = root.FirstChildElement(); i; i = i->NextSiblingElement()) {
    Component::Ptr comp = createComponent(i);
    actor->addComponent(comp);
  }
  
  return actor;
}

Game::Component::Ptr Game::ActorFactory::createComponent(const tinyxml2::XMLElement *node) {
  Component::Ptr comp;
  
  auto iter = creators.find(node->Value());
  if (iter != creators.end()) {
    comp.reset(iter->second());
  } else {
    throw std::runtime_error("Failed to find creator");
  }
  
  comp->init(node);
  
  return comp;
}
