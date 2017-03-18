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
  iterating = true;
  
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
  
  iterating = false;
  removeIterators();
  addListeners();
}

void EventManager::emit(const Event::Ptr msg) {
  assert(msg);
  PROFILE(Event manager emit);
  
  queue[currentQueue].push_back(msg);
}

void EventManager::emitNow(const Event::Ptr msg) {
  assert(msg);
  PROFILE(Event manager emitNow);
  
  bool userCalled = false;
  if (!iterating) {
    userCalled = true;
    iterating = true;
  }
  
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
  
  if (userCalled) {
    iterating = false;
    removeIterators();
    addListeners();
  }
}

EventManager::ListenerID EventManager::addListener(Event::Type type, const Listener &listener) {
  assert(listener);
  PROFILE(Event manager addListener);
  
  const ListenerID id = idGen.make();
  if (iterating) {
    newListeners[type].emplace(id, listener);
  } else {
    listeners[type].emplace(id, listener);
  }
  return id;
}

void EventManager::remListener(Event::Type type, ListenerID id) {
  PROFILE(Event manager remListener);

  if (iterating) {
    auto iter = listeners.find(type);
    if (iter != listeners.end()) {
      auto listenerIter = iter->second.find(id);
      if (listenerIter != iter->second.end()) {
        iterators[type].push_back(listenerIter);
        return;
      }
    }
  } else {
    auto iter = listeners.find(type);
    if (iter != listeners.end()) {
      if (iter->second.erase(id)) {
        if (iter->second.empty()) {
          listeners.erase(iter);
        }
        return;
      }
    }
  }
  LOG_WARNING(GAME_EVENTS, "Tried to remove event listener but it wasn't found");
}

EventManager::ListenerID EventManager::addListener(const Listener &listener) {
  assert(listener);
  PROFILE(Event manager add universal listener);
  
  const ListenerID id = idGen.make();
  if (iterating) {
    anyNewListeners.emplace(id, listener);
  } else {
    anyListeners.emplace(id, listener);
  }
  return id;
}

void EventManager::remListener(ListenerID id) {
  PROFILE(Event manager rem universal listener);
  
  if (iterating) {
    auto iter = anyListeners.find(id);
    if (iter != anyListeners.end()) {
      anyIterators.push_back(iter);
      return;
    }
  } else {
    if (anyListeners.erase(id)) {
      return;
    }
  }
  LOG_WARNING(GAME_EVENTS, "Tried to remove event listener but it wasn't found");
}

void EventManager::removeIterators() {
  PROFILE(Event manager remove iterators);

  for (auto e = iterators.begin(); e != iterators.end(); ++e) {
    auto listenerEvent = listeners.find(e->first);
    assert(listenerEvent != listeners.end());
    for (auto l = e->second.begin(); l != e->second.end(); ++l) {
      listenerEvent->second.erase(*l);
    }
  }
  iterators.clear();
  for (auto e = listeners.begin(); e != listeners.end();) {
    if (e->second.empty()) {
      e = listeners.erase(e);
    } else {
      ++e;
    }
  }
  
  for (auto l = anyIterators.begin(); l != anyIterators.end(); ++l) {
    anyListeners.erase(*l);
  }
  anyIterators.clear();
}

void EventManager::addListeners() {
  PROFILE(Event manager add listeners);

  for (auto e = newListeners.begin(); e != newListeners.end(); ++e) {
    listeners[e->first].insert(e->second.begin(), e->second.end());
  }
  newListeners.clear();

  anyListeners.insert(anyNewListeners.begin(), anyNewListeners.end());
  anyNewListeners.clear();
}
