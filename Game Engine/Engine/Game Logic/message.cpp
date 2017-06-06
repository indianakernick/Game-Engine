//
//  message.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "message.hpp"

Game::Message::Message(const ID id, const Any data)
  : data(data), id(id) {}

Game::MissingMessenger::MissingMessenger(const char *what)
  : std::runtime_error(what) {}
