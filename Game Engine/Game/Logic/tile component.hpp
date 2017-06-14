//
//  tile component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_tile_component_hpp
#define game_logic_tile_component_hpp

#include "Events/tile.hpp"
#include "../../Engine/Math/dir.hpp"
#include "../../Engine/Event/manager.hpp"
#include "../../Engine/Game Logic/component.hpp"
#include "../../Engine/Utils/member function.hpp"

namespace Game {
  class TileComponent : public Component {
  public:
    using Ptr = std::shared_ptr<TileComponent>;
    
    using Neighbors = std::array<TileComponent *, 4>;
    
    class IOTypeMismatch final : public std::runtime_error {
    public:
      explicit IOTypeMismatch(const char *);
    };
  
    TileComponent();
    ~TileComponent();
    
    void onMessage(const Message &) override;
    
    void preUpdate();
    void updateInputStates(const Neighbors &);
    
    TileIOType getIOType(Math::Dir) const;
    TileIOType getIOType(size_t) const;
    TileIOTypes getIOTypes() const;
    
  protected:
    void setOutput(Math::Dir, bool);
    void setOutput(size_t, bool);
    
    //set the output state if the side is an output
    
    void setOutputIfCan(Math::Dir, bool);
    void setOutputIfCan(size_t, bool);
    
    void setAllOutputs(bool);
    void setAllOutputs(TileStates);
    
    TileStates getAllInputs() const;
    
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
    
    TileStates inputStates;
    TileStates outputStates;
    TileIOTypes ioTypes = {};
    
    void onIOChange(std::shared_ptr<Events::TileIOChange>);
  };
}

#endif
