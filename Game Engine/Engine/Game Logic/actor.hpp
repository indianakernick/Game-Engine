//
//  actor.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_actor_hpp
#define engine_game_logic_actor_hpp

#include <queue>
#include <memory>
#include <vector>
#include "component.hpp"
#include "../Utils/safe down cast.hpp"

namespace Game {
  class MissingComponent final : public std::runtime_error {
  public:
    explicit MissingComponent(const char *);
  };
  
  class DuplicateComponent final : public std::runtime_error {
  public:
    DuplicateComponent();
  };
  
  class BadParentPtr final : public std::runtime_error {
  public:
    explicit BadParentPtr(const char *);
  };

  class Actor final : public MessageManager<Component::ID> {
  friend class ActorFactory;
  friend class Component;
  public:
    using Ptr = std::shared_ptr<Actor>;
    using ID = uint32_t;
    
    static const ID NULL_ID;
    
    explicit Actor(ID);
    ~Actor() = default;
    
    template<typename Comp>
    std::weak_ptr<Comp> getComponent() {
      const Component::ID id = GetComponentID<Comp>::get();
      if (id < components.size() && components[id]) {
        return safeDownCast<Comp>(components[id]);
      }
      throw MissingComponent("Tried to get a component that doesn't exist");
    }
    
    template <typename Comp>
    std::enable_if_t<std::is_base_of<Component, Comp>::value, void>
    addComponent(std::shared_ptr<Comp> comp) {
      assert(comp);
      if (comp->actor == this) {
        throw BadParentPtr("Cannot add component to same actor twice");
      } else if (comp->actor != nullptr) {
        throw BadParentPtr("Cannot add component to more than one actor");
      }
      
      const Component::ID id = GetComponentID<Comp>::get();
      if (id < components.size()) {
        if (components[id]) {
          throw DuplicateComponent();
        } else {
          components[id] = comp;
        }
      } else {
        const size_t id = id;
        do {
          components.emplace_back();
        } while (components.size() <= id);
        components[id] = comp;
      }
      
      comp->actor = this;
    }
    
    ID getID() const;
    void update(uint64_t);
    
  private:
    ID id;
    
    std::vector<Component::Ptr> components;
    
    using MessageManager::broadcastMessage;
    using MessageManager::sendMessage;
    using MessageManager::flushMessages;
    
    void flushMessages();
    Messenger<Component::ID> *getMessenger(Component::ID) const override;
    Component::ID getNumMessengers() const override;
  };
}

#endif
