//
//  subject.hpp
//  game engine
//
//  Created by Indi Kernick on 4/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef subject_hpp
#define subject_hpp

#include <functional>
#include <map>
#include <set>
#include <ID/rand.hpp>

template <typename DATA>
class SubjectID {
public:
  typedef ID::Type IDType;
  typedef std::function<void (DATA)> Observer;
  
  IDType addObserver(Observer ob) {
    IDType id = idGen.create();
    observers[id] = ob;
    return id;
  }
  void remObserver(IDType id) {
    observers.erase(id);
    idGen.remove(id);
  }
protected:
  void dispatch(DATA data) {
    for (auto i = observers.begin(); i != observers.end(); ++i) {
      i->second(data);
    }
  }
private:
  std::map<IDType, Observer> observers;
  ID::Rand idGen;
};

template <typename DATA>
class SubjectFunc {
public:
  //i would normally use std::function instead of function pointers
  //but i cant get std::function::target to work
  typedef void(*Observer)(DATA);
  
  SubjectFunc() = default;
  virtual ~SubjectFunc() = default;
  
  void addObserver(Observer ob) {
    observers.insert(ob);
  }
  void remObserver(Observer ob) {
    observers.erase(ob);
  }
protected:
  void dispatch(DATA data) {
    for (auto i = observers.begin(); i != observers.end(); ++i) {
      (*i)(data);
    }
  }
private:
  std::set<Observer> observers;
};

#endif