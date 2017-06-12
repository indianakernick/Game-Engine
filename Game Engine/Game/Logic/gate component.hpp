//
//  gate component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_gate_component_hpp
#define game_logic_gate_component_hpp

#include <bitset>
#include "tile component.hpp"
#include "../../Engine/Event/manager.hpp"
#include "../../Engine/Game Logic/actor.hpp"
#include "../../Engine/Utils/member function.hpp"

namespace Game {
  class GateTable {
  public:
    GateTable() = default;
    ~GateTable() = default;
    
    ///Get the output states for a given set of input states
    TileComponent::States lookUpOutputs(TileComponent::States) const;
    ///Set the output states for a given set of input states
    void setOutputForInput(TileComponent::States, TileComponent::States);
    ///Tell the GateTable which sides are inputs and which sides are outputs
    void setIOSides(TileComponent::IOTypes);
    
  private:
    /*
    Each set of bits between commas are rows
    The columns in a row represent the output state
    Each combination of input states has a row
    
    0 0 0 0          table when there are 0 inputs  row is 4 bits wide
    1 1 1,1 1 1      table when there are 1 inputs  row is 3 bits wide
    2 2,2 2,2 2,2 2  table when there are 2 inputs  row is 2 bits wide
    3,3,3,3,3,3,3,3  table when there are 3 inputs  row is 1 bits wide
                     table when there are 4 inputs  row is 0 bits wide
    */
  
    std::bitset<8> table;
    //which sides are inputs
    TileComponent::States inputs;
    //which sides are outputs
    TileComponent::States outputs;
    
    //returns the index of the first bit in the row for a set of input states
    size_t getRowIndex(TileComponent::States) const;
  };

  namespace Events {
    constexpr char GATE_TABLE_CHANGE_NAME[] = "Gate Table Change";
    
    class GateTableChange final : public StaticEvent<GateTableChange, GATE_TABLE_CHANGE_NAME> {
    public:
      GateTableChange(Actor::ID, GateTable);
      
      const Actor::ID gateID;
      const GateTable table;
    };
  }
  
  class Gate final : public TileComponent {
  public:
    Gate();
    ~Gate();
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
    
  private:
    EventManager::ListenerID tableChangeID;
    GateTable table;
    
    void onTableChange(Events::GateTableChange::Ptr);
  };
}

#endif
