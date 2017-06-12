//
//  tile component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_tile_component_hpp
#define game_logic_tile_component_hpp

#include <array>
#include <bitset>
#include "../../Engine/Math/dir.hpp"
#include "../../Engine/Event/manager.hpp"
#include "../../Engine/Game Logic/actor.hpp"
#include "../../Engine/Game Logic/component.hpp"
#include "../../Engine/Utils/member function.hpp"

namespace Game {
  namespace Events {
    constexpr char TILE_IO_CHANGE_NAME[] = "Tile IO Change";
    
    class TileIOChange;
  }

  class TileComponent : public Component {
  public:
    enum class IOType {
      NONE,
      IN,
      OUT
    };
  
    using Neighbors = std::array<TileComponent *, 4>;
    using States = std::bitset<4>;
    using IOTypes = std::array<IOType, 4>;
    
    class IOTypeMismatch final : public std::runtime_error {
    public:
      explicit IOTypeMismatch(const char *);
    };
  
    TileComponent();
    ~TileComponent();
    
    void onMessage(const Message &) override;
    
    void preUpdate();
    void updateInputStates(const Neighbors &);
    
    IOType getIOType(Math::Dir) const;
    IOType getIOType(size_t) const;
    IOTypes getIOTypes() const;
    
  protected:
    void setOutput(Math::Dir, bool);
    void setOutput(size_t, bool);
    
    //set the output state if the side is an output
    
    void setOutputIfCan(Math::Dir, bool);
    void setOutputIfCan(size_t, bool);
    
    void setAllOutputs(bool);
    void setAllOutputs(States);
    
    States getAllInputs() const;
    
    bool getInput(Math::Dir) const;
    bool getInput(size_t) const;
    
    bool getInputOr(Math::Dir, bool) const;
    bool getInputOr(size_t, bool) const;
    
    bool allInputEqualTo(bool) const;
    bool anyInputEqualTo(bool) const;
    bool noneInputEqualTo(bool) const;
    size_t numInputEqualTo(bool) const;
    
    bool allInputOn() const;
    bool anyInputOn() const;
    bool noneInputOn() const;
    size_t numInputOn() const;
    
    size_t countInputs() const;
    size_t countOutputs() const;
    bool noIO() const;
    
  private:
    EventManager::ListenerID ioChangeID;
    
    States inputStates;
    States outputStates;
    IOTypes ioTypes = {};
    
    void onIOChange(std::shared_ptr<Events::TileIOChange>);
  };
  
  namespace Events {
    class TileIOChange final : public StaticEvent<TileIOChange, TILE_IO_CHANGE_NAME> {
    public:
      TileIOChange(Actor::ID, TileComponent::IOTypes);
      
      const Actor::ID tileID;
      const TileComponent::IOTypes ioTypes;
    };
  }
}

#endif
