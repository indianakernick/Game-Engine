//
//  component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "component.hpp"

void Component::broadcastMessage(int id, void *data) {
  if (actor) {
    actor->messageQueue.emplace(getID(), Actor::ALL_COMPONENTS, id, data);
  } else {
    throw std::runtime_error("Could not broadcast message because this component is not connected to an Actor");
  }
}

void Component::sendMessage(Component::ID to, int id, void *data) {
  if (actor) {
    actor->messageQueue.emplace(getID(), to, id, data);
  } else {
    throw std::runtime_error("Could not send message because this component is not connected to an Actor");
  }
}

void Component::setActor(ActorPtr newActor) {
  actor = newActor;
}
