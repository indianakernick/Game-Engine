//
//  actor factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "actor factory.hpp"

Game::DuplicateCreator::DuplicateCreator()
  : std::runtime_error("Tried to register two creators with the same name") {}

Game::MissingCreator::MissingCreator()
  : std::runtime_error("Failed to find creator") {}

Game::ActorFactory::ActorFactory() {
  idGen.nextIsAfter(Actor::NULL_ID);
}

Game::Actor::Ptr Game::ActorFactory::createActor(const std::string &xmlFile) {
  Actor::Ptr actor = std::make_shared<Actor>(idGen.make());
  
  Res::XML::Ptr xmlDoc = Res::XMLManager::getSingleton().load(
    xmlFile,
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::XML>();
  
  const tinyxml2::XMLElement *root = xmlDoc->getRoot();
  
  for (const tinyxml2::XMLElement *e = root->FirstChildElement(); e; e = e->NextSiblingElement()) {
    addComponent(actor, e);
  }
  
  return actor;
}

void Game::ActorFactory::addComponent(
  const Actor::Ptr actor,
  const tinyxml2::XMLElement *element
) const {
  auto iter = creators.find(element->Value());
  if (iter != creators.cend()) {
    iter->second(actor, element);
  } else {
    throw MissingCreator();
  }
}
