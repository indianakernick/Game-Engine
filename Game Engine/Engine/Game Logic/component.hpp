//
//  component.hpp
//  game engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

#include <memory>
#include "../Serial/xml.hpp"

class Actor;
using ActorPtr = std::shared_ptr<Actor>;

class Component {
friend class ActorFactory;
public:
  using ID = char;

  Component() = default;
  virtual ~Component() = default;
  
  virtual void init(XML::NodePtr) = 0;
  
  virtual ID getID() const = 0;
  virtual void update(double) = 0;
  
protected:
  ActorPtr actor;
private:
  void setActor(ActorPtr);
};

using ComponentPtr = std::shared_ptr<Component>;

#endif
