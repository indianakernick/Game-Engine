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

Game::Actor::Ptr Game::ActorFactory::createActor(const std::string &xmlFile, const Actor::ID id) {
  Res::XML::Ptr xmlDoc = Res::XMLManager::getSingleton().load(
    xmlFile,
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::XML>();
  
  return createActor(xmlDoc->getRoot(), id);
}

Game::Actor::Ptr Game::ActorFactory::createActor(
  const tinyxml2::XMLElement *element,
  const Actor::ID id
) {
  Actor::Ptr actor = std::make_shared<Actor>(id);
  
  for (
    const tinyxml2::XMLElement *e = element->FirstChildElement();
    e;
    e = e->NextSiblingElement()
  ) {
    auto iter = creators.find(e->Name());
    if (iter != creators.end()) {
      iter->second(actor, e);
    } else {
      throw MissingCreator();
    }
  }
  
  return actor;
}
