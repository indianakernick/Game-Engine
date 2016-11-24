//
//  broadcast.cpp
//  Game Engine
//
//  Created by Indi Kernick on 29/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "broadcast.hpp"

using namespace Message::Broadcast;

Pool::Pool(bool deleteComs)
  : deleteComs(deleteComs) {

}

Pool::~Pool() {
  if (deleteComs) {
    for (Com* com : coms) {
      delete com;
    }
  }
}

void Pool::add(Com* com) {
  assert(com);
  assert(com->pool == nullptr);
  com->pool = this;
  coms.push_front(com);
}

void Pool::rem(Com* com) {
  assert(com);
  coms.remove(com);
}

void Pool::pump() {
  while (!msgs.empty()) {
    Message msg = msgs.front();
    msgs.pop();
    for (Com* com : coms) {
      if (msg.sender != com) {
        com->receive(msg.msg);
      }
    }
  }
}

void Pool::send(const Broadcast::Message& message) {
  msgs.push({message, nullptr});
}

void Pool::send(const Broadcast::Message& message, Com* sender) {
  msgs.push({message, sender});
}

Com::~Com() {
  pool = nullptr;
}

void Com::send(const Broadcast::Message& message) {
  assert(pool);
  pool->send(message, this);
}
