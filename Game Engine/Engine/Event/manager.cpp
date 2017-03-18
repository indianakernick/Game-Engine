//
//  manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

using namespace Game;

std::unique_ptr<EventManager> evtMan = nullptr;

EventManager::EventManager(uint64_t timeLimit)
  : timeLimit(timeLimit) {}

EventManager::~EventManager() {
  if (!queue[currentQueue].empty()) {
    LOG_WARNING(GAME_EVENTS,
      "%lu events weren't processed before dtor",
      queue[currentQueue].size());
  }
  if (!anyListeners.empty()) {
    LOG_WARNING(GAME_EVENTS,
      "%lu universal listeners weren't removed before dtor",
      anyListeners.size());
  }
  if (!listeners.empty()) {
    size_t sum = 0;
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
      sum += i->second.size();
    }
    LOG_WARNING(GAME_EVENTS,
      "%lu listeners weren't removed before dtor",
      sum);
  }
}

void EventManager::update() {
  PROFILE(Event manager update);
  
  Time::StopWatch<std::chrono::nanoseconds> stopwatch(true);
  const uint8_t processingQueue = currentQueue;
  currentQueue = (currentQueue + 1) & 1;
  
  while (!queue[processingQueue].empty()) {
    const Event::Ptr event = queue[processingQueue].front();
    queue[processingQueue].pop_front();
    emitNow(event);
    if (stopwatch.get() >= timeLimit) {
      break;
    }
  }
  
  if (!queue[processingQueue].empty()) {
    LOG_DEBUG(GAME_EVENTS,
      "Not enough time to process all events. %lu events weren't processed",
      queue[processingQueue].size());
    
    queue[currentQueue].insert(queue[currentQueue].begin(),
                               queue[processingQueue].begin(),
                               queue[processingQueue].end());
    queue[processingQueue].clear();
  }
}

void EventManager::emit(const Event::Ptr msg) {
  assert(msg);
  queue[currentQueue].push_back(msg);
}

void EventManager::emitNow(const Event::Ptr msg) {
  assert(msg);
  auto iter = listeners.find(msg->getType());
  if (iter != listeners.end()) {
    const Listeners &listenersList = iter->second;
    for (auto l = listenersList.begin(); l != listenersList.end(); ++l) {
      (l->second)(msg);
    }
  }
  for (auto l = anyListeners.begin(); l != anyListeners.end(); ++l) {
    (l->second)(msg);
  }
}

EventManager::ListenerID EventManager::addListener(Event::Type type, const Listener &listener) {
  assert(listener);
  const ListenerID id = idGen.make();
  listeners[type].emplace(id, listener);
  return id;
}

void EventManager::remListener(Event::Type type, ListenerID id) {
  auto iter = listeners.find(type);
  if (iter != listeners.end()) {
    if (iter->second.erase(id)) {
      if (iter->second.empty()) {
        listeners.erase(iter);
      }
      return;
    }
  }
  LOG_WARNING(GAME_EVENTS, "Tried to remove event listener but it wasn't found");
}

EventManager::ListenerID EventManager::addListener(const Listener &listener) {
  assert(listener);
  const ListenerID id = idGen.make();
  anyListeners.emplace(id, listener);
  return id;
}

void EventManager::remListener(ListenerID id) {
  if (!anyListeners.erase(id)) {
    LOG_WARNING(GAME_EVENTS, "Tried to remove event listener but it wasn't found");
  }
}
