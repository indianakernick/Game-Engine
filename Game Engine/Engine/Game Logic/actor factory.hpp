//
//  actor factory.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_actor_factory_hpp
#define engine_game_logic_actor_factory_hpp

#include <string>
#include "actor.hpp"
#include <unordered_map>
#include "../ID/local.hpp"
#include "../Resource/Managers/xml.hpp"

namespace Game {
  class DuplicateCreator final : public std::runtime_error {
  public:
    DuplicateCreator();
  };
  
  class MissingCreator final : public std::runtime_error {
  public:
    MissingCreator();
  };
  
  class ActorFactory {
  public:
    ActorFactory();
    ~ActorFactory() = default;
    
    //BaseComp is a direct descendant of Component and
    //Comp is direct descendant of BaseComp
    
    ///Register a name for a Component class
    template <typename BaseComp, typename Comp>
    std::enable_if_t<
      std::is_base_of<Component, BaseComp>::value &&
      std::is_base_of<BaseComp, Comp>::value &&
      !std::is_same<Component, BaseComp>::value &&
      !std::is_same<BaseComp, Comp>::value &&
      std::is_default_constructible<Comp>::value
    >
    addCreator(const std::string &name) {
      if (!creators.emplace(name, &creator<BaseComp, Comp>).second) {
        throw DuplicateCreator();
      }
    }
    Actor::Ptr createActor(const std::string &);
    Actor::Ptr createActor(const std::string &, Actor::ID);

  private:
    template <typename BaseComp, typename Comp>
    static void creator(const Actor::Ptr actor, const tinyxml2::XMLElement *element) {
      const std::shared_ptr<Comp> comp = std::make_shared<Comp>();
      comp->init(element);
      actor->addComponent(std::static_pointer_cast<BaseComp>(comp));
    }
  
    using Creator = void (*)(Actor::Ptr, const tinyxml2::XMLElement *);
    using CreatorMap = std::unordered_map<std::string, Creator>;
    CreatorMap creators;
    ID::Local<Actor::ID> idGen;
    
    void addComponent(Actor::Ptr, const tinyxml2::XMLElement *) const;
  };
}

#endif
