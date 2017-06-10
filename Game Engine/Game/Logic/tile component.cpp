//
//  tile component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "tile component.hpp"

void Game::TileComponent::update(uint64_t) {}

void Game::TileComponent::onMessage(const Message &) {}

void Game::TileComponent::updateInputStates(const Neighbors &neighbors) {
  for (size_t n = 0; n != neighbors.size(); n++) {
    const TileComponent *neighbor = neighbors[n];
    if (ioTypes[n] == IOType::IN && neighbor) {
      if (neighbor->getIOType(Math::oppositeDir(n)) != IOType::OUT) {
        inputStates.reset(n);
      } else {
        inputStates.set(neighbor->getInput(n));
      }
    }
  }
}

Game::TileComponent::IOTypeMismatch::IOTypeMismatch(const char *what)
  : std::runtime_error(what) {}

void Game::TileComponent::setIOType(const Math::Dir dir, const IOType type) {
  const size_t i = Math::toInt<size_t>(dir);
  if (ioTypes[i] != type) {
    inputStates.reset(i);
    outputStates.reset(i);
    ioTypes[i] = type;
  }
}

Game::TileComponent::IOType Game::TileComponent::getIOType(const Math::Dir dir) const {
  return ioTypes[Math::toInt<size_t>(dir)];
}

Game::TileComponent::IOType Game::TileComponent::getIOType(const size_t dir) const {
  assert(Math::validDir(dir));
  return ioTypes[dir];
}

void Game::TileComponent::setOutput(const Math::Dir dir, const bool state) {
  setOutput(Math::toInt<size_t>(dir), state);
}

void Game::TileComponent::setOutput(const size_t index, const bool state) {
  if (ioTypes[index] == IOType::OUT) {
    outputStates.set(index, state);
  } else {
    throw IOTypeMismatch("Tried to set the output state of a side that wasn't an output");
  }
}

void Game::TileComponent::setAllOutputs(const bool state) {
  outputStates.set(state);
}

bool Game::TileComponent::getInput(const Math::Dir dir) const {
  return getInput(Math::toInt<size_t>(dir));
}

bool Game::TileComponent::getInput(const size_t index) const {
  assert(Math::validDir(index));
  if (ioTypes[index] == IOType::IN) {
    return inputStates.test(index);
  } else {
    throw IOTypeMismatch("Tried to get the input state of a side that wasn't an input");
  }
}

bool Game::TileComponent::allInputEqualTo(const bool state) const {
  if (state) {
    return inputStates.count() == countInputs();
  } else {
    return inputStates.none();
  }
}

bool Game::TileComponent::anyInputEqualTo(const bool state) const {
  if (state) {
    return inputStates.any();
  } else {
    return inputStates.count() < countInputs();
  }
}

bool Game::TileComponent::noneInputEqualTo(const bool state) const {
  if (state) {
    return inputStates.none();
  } else {
    return inputStates.count() == countInputs();
  }
}

size_t Game::TileComponent::numInputEqualTo(const bool state) const {
  if (state) {
    return inputStates.count();
  } else {
    return countInputs() - inputStates.count();
  }
}

size_t Game::TileComponent::countInputs() const {
  return static_cast<size_t>(ioTypes[0] == IOType::IN) +
         static_cast<size_t>(ioTypes[1] == IOType::IN) +
         static_cast<size_t>(ioTypes[2] == IOType::IN) +
         static_cast<size_t>(ioTypes[3] == IOType::IN);
}

size_t Game::TileComponent::countOutputs() const {
  return static_cast<size_t>(ioTypes[0] == IOType::OUT) +
         static_cast<size_t>(ioTypes[1] == IOType::OUT) +
         static_cast<size_t>(ioTypes[2] == IOType::OUT) +
         static_cast<size_t>(ioTypes[3] == IOType::OUT);
}

bool Game::TileComponent::noIO() const {
  return ioTypes[0] == IOType::NONE &&
         ioTypes[1] == IOType::NONE &&
         ioTypes[2] == IOType::NONE &&
         ioTypes[3] == IOType::NONE;
}
