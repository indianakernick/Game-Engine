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
  //@TODO
  //surely there must be an elegent solution to this problem
  //maybe the table needs to be more dynamic, like a std::vector<bool>
  //maybe the table shouldn't be a 2D array

  /*

  the zero cells are not needed
  ideally we only need 15 bits

          number of
          outputs

          1 2 3 4
          _______
  n   0  |1 1 1 1|
  u   1  |1 1 1 0|
  m      |1 1 0 0|
  b   2  |1 1 0 0|
  e      |1 0 0 0|
  r      |1 0 0 0|
         |1 0 0 0|
  o   3  |1 0 0 0|
  f      |0 0 0 0|
         |0 0 0 0|
  i      |0 0 0 0|
  n      |0 0 0 0|
  p      |0 0 0 0|
  u      |0 0 0 0|
  t      |0 0 0 0|
  s   4  |0 0 0 0|
          -------

  */

  class GateTable {
  public:
    using Row = std::bitset<4>;
    
    GateTable();
    ~GateTable() = default;
    
    Row lookUpOutputs(Row) const;
    
    void setRow(size_t, Row);
    
  private:
    //A table with 16 rows and 4 columns
    //Each column represents an output side and
    //each row represents a combination of inputs
    using Table = std::bitset<64>;
    Table table;
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
