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
    const Listeners &listenersVector = iter->second;
    for (auto h = listenersVector.begin(); h != listenersVector.end(); ++h) {
      (*h)(msg);
    }
  }
  for (auto h = anyListeners.begin(); h != anyListeners.end(); ++h) {
    (*h)(msg);
  }
}

void EventManager::addListener(Event::Type type, const Listener &listener) {
  assert(listener);
  listeners[type].push_back(listener);
}

void EventManager::remListener(Event::Type type, const Listener &listener) {
  assert(listener);
  //this function will rarely be called to it doesn't matter how slow it is
  auto iter = listeners.find(type);
  if (iter != listeners.end()) {
    Listeners &listenersVector = iter->second;
    std::equal_to<Listener> equal;
    for (auto h = listenersVector.begin(); h != listenersVector.end(); ++h) {
      if (equal(listener, *h)) {
        listenersVector.erase(h);
        if (listenersVector.empty()) {
          listeners.erase(iter);
        }
        return;
      }
    }
  }
  
  LOG_WARNING(GAME_EVENTS, "Tried to remove event listener but it wasn't found");
}

void EventManager::addListener(const Listener &listener) {
  assert(listener);
  anyListeners.push_back(listener);
}

void EventManager::remListener(const Listener &listener) {
  assert(listener);
  std::equal_to<Listener> equal;
  for (auto h = anyListeners.begin(); h != anyListeners.end(); ++h) {
    if (equal(listener, *h)) {
      anyListeners.erase(h);
      return;
    }
  }
  
  LOG_WARNING(GAME_EVENTS, "Tried to remove event listener but it wasn't found");
}

bool std::equal_to<EventManager::Listener>::operator()(
  const EventManager::Listener &a,
  const EventManager::Listener &b
) const {
  return a.target<EventManager::Listener>() == b.target<EventManager::Listener>();
}
