//
//  actor factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "actor factory.hpp"

Game::DuplicateCreator::DuplicateCreator()
  : std::runtime_error("Duplicate creator") {}

Game::MissingCreator::MissingCreator()
  : std::runtime_error("Failed to find creator") {}

Game::ActorFactory::ActorFactory() {
  idGen.nextIsAfter(Actor::NULL_ID);
}

void Game::ActorFactory::addCreator(const std::string &name, const ComponentCreator &creator) {
  if (!creators.emplace(name, creator).second) {
    throw DuplicateCreator();
  }
}

Game::Actor::Ptr Game::ActorFactory::createActor(const std::string &xmlFile) {
  Actor::Ptr actor = std::make_shared<Actor>(idGen.make());
  
  Res::XML::Ptr xmlDoc = Res::XMLManager::getSingleton().load(
    xmlFile,
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::XML>();
  
  const tinyxml2::XMLElement *root = xmlDoc->getRoot();
  
  for (const tinyxml2::XMLElement *e = root->FirstChildElement(); e; e = e->NextSiblingElement()) {
    actor->addComponent(createComponent(e));
  }
  
  return actor;
}

Game::Component::Ptr Game::ActorFactory::createComponent(const tinyxml2::XMLElement *node) {
  auto iter = creators.find(node->Value());
  if (iter != creators.end()) {
    const Component::Ptr comp = iter->second();
    comp->init(node);
    return comp;
  } else {
    throw MissingCreator();
  }
}
