//
//  manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

void Game::EventManager::addListener(Event::Type eventType, const Listener &listener) {
  ListenerList list = listeners[eventType];
  for (auto i = list.begin(); i != list.end(); ++i) {
    if (compare(*i, listener)) {
      LOG_ERROR(GAME_EVENTS,
        "The same listener was added twice to listen to event type %ull",
        eventType);
      return;
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
  LOG_WARNING(GAME_EVENTS,
    "Tried to remove a listener of type %llu but it was not found",
    eventType);
  return false;
}

void Game::EventManager::triggerNow(Event::Ptr event) {
  auto iter = listeners.find(event->getType());
  if (iter != listeners.end()) {
    ListenerList &list = iter->second;
    if (!list.empty()) {
      for (auto i = list.begin(); i != list.end(); ++i) {
        (*i)(event);
      }
      return;
    }
  }
  LOG_WARNING(GAME_EVENTS, "triggerNow called no listeners");
}

void Game::EventManager::trigger(Event::Ptr event) {
  queues[activeQueue].push(event);
  if (listeners.find(event->getType()) == listeners.end()) {
    LOG_WARNING(GAME_EVENTS,
      "trigger called with event %llu but no listeners will be called",
      event->getType());
  }
}

void Game::EventManager::update(Task::Delta) {
  uint8_t procQueue = activeQueue;
  activeQueue = (activeQueue + 1) % 2;
  
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
