//
//  manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

Game::EventManager::EventManager()
#ifdef DEBUG
  : logger("events.log")
#endif
  {}

void Game::EventManager::addListener(Event::Type eventType, const Listener &listener) {
  ListenerList list = listeners[eventType];
  for (auto i = list.begin(); i != list.end(); ++i) {
    if (compare(*i, listener)) {
      throw std::runtime_error("Duplicate listener");
    }
  }
  list.push_back(listener);
}

bool Game::EventManager::remListener(Event::Type eventType, const Listener &listener) {
  auto iter = listeners.find(eventType);
  if (iter != listeners.end()) {
    ListenerList &list = iter->second;
    for (auto i = list.begin(); i != list.end(); ++i) {
      if (compare(*i, listener)) {
        list.erase(i);
        return true;
      }
    }
  }
  #ifdef DEBUG
  logger.write("Tried to remove a listener of type ",eventType," but it was not found");
  #endif
  return false;
}

void Game::EventManager::triggerNow(Event::Ptr event) {
  #ifdef DEBUG
  logger.write("triggerNow called with event type ",event->getType());
  #endif
  auto iter = listeners.find(event->getType());
  if (iter != listeners.end()) {
    ListenerList &list = iter->second;
    if (!list.empty()) {
      #ifdef DEBUG
      logger.write("triggerNow called ",list.size()," listeners");
      #endif
      for (auto i = list.begin(); i != list.end(); ++i) {
        (*i)(event);
      }
      return;
    }
  }
  #ifdef DEBUG
  logger.write("triggerNow called no listeners");
  #endif
}

void Game::EventManager::trigger(Event::Ptr event) {
  queues[activeQueue].push(event);
  #ifdef DEBUG
  logger.write("triggerLater called with event type ", event->getType());
  auto iter = listeners.find(event->getType());
  if (iter != listeners.end()) {
    ListenerList &list = iter->second;
    if (!list.empty()) {
      logger.write("There are ",list.size()," listeners that will be called next frame");
      return;
    }
  }
  logger.write("There are no listeners that will be called next frame");
  #endif
}

void Game::EventManager::update(Task::Delta) {
  uint8_t procQueue = activeQueue;
  activeQueue = (activeQueue + 1) % 2;
  
  #ifdef DEBUG
  logger.write("Removed ",queues[procQueue].size()," events from event queue");
  #endif
  
  while (!queues[procQueue].empty()) {
    Event::Ptr event = queues[procQueue].front();
    queues[procQueue].pop();
    
    auto iter = listeners.find(event->getType());
    if (iter != listeners.end()) {
      ListenerList &list = iter->second;
      for (auto i = list.begin(); i != list.end(); ++i) {
        (*i)(event);
      }
    }
  }
}

bool Game::EventManager::compare(const Listener &a, const Listener &b) {
  return a.target<Listener>() == b.target<Listener>();
}
