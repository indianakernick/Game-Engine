//
//  tile component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_tile_component_hpp
#define game_logic_tile_component_hpp

#include "../../Engine/Game Logic/component.hpp"
#include "../../Engine/Math/dir.hpp"
#include <bitset>
#include <array>

namespace Game {
  class TileComponent : public Component {
  public:
    using Neighbors = std::array<TileComponent *, 4>;
  
    TileComponent() = default;
    ~TileComponent() = default;
    
    void onMessage(const Message &) override;
    
    void preUpdate();
    void updateInputStates(const Neighbors &);
    
    enum class IOType {
      NONE,
      IN,
      OUT
    };
    
    class IOTypeMismatch final : public std::runtime_error {
    public:
      explicit IOTypeMismatch(const char *);
    };
    
    void setIOType(Math::Dir, IOType);
    IOType getIOType(Math::Dir) const;
    IOType getIOType(size_t) const;
    
  protected:
    void setOutput(Math::Dir, bool);
    void setOutput(size_t, bool);
    void setAllOutputs(bool);
    
    bool getInput(Math::Dir) const;
    bool getInput(size_t) const;
    
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
    //I can either save one byte and use one bitset or save a few clock cycles
    //and use two bitsets
    std::bitset<4> inputStates;
    std::bitset<4> outputStates;
    IOType ioTypes[4] = {};
  };
}

#endif
