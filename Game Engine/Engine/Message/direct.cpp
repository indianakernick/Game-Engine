//
//  direct.cpp
//  Game Engine
//
//  Created by Indi Kernick on 29/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "direct.hpp"

using namespace Message::Direct;

Pool::Pool(bool deleteComs)
  : deleteComs(deleteComs) {
  
}

Pool::~Pool() {
  if (deleteComs) {
    for (auto pair : coms) {
      delete pair.second;
    }
  }
}

void Pool::add(int id, Com* com) {
  assert(com);
  assert(com->pool == nullptr);
  com->pool = this;
  coms[id] = com;
}

void Pool::rem(int id) {
  coms.erase(id);
}

void Pool::pump() {
  while (!msgs.empty()) {
    Message msg = msgs.front();
    msgs.pop();
    coms[msg.receiverID]->recieve(msg.msg);
  }
}

void Pool::send(const Direct::Message& message, int receiverID) {
  msgs.push({message, receiverID});
}

Com::~Com() {
  pool = nullptr;
}

void Com::send(const Direct::Message& message, int receiverID) {
  assert(pool);
  pool->send(message, receiverID);
}

int Com::getID() {
  return id;
}
