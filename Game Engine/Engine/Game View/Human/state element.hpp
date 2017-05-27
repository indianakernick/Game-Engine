//
//  state element.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_state_element_hpp
#define engine_game_view_human_state_element_hpp

#include "element.hpp"
#include "../../Utils/dispatcher.hpp"

namespace UI {
  class StateElement : public Element {
  public:
    using Ptr = std::shared_ptr<StateElement>;
    
    enum class ButtonState : uint8_t {
      DOWN_OUT,
      OUT,
      HOVER,
      DOWN
    };
    using SubState = uint8_t;
    
    struct State {
      ButtonState buttonState;
      SubState subState;
      
      bool operator==(State) const;
      bool operator!=(State) const;
    };
    
  private:
    using StateChangeNotif   = Observable <      StateElement &, State, State>;
    using StateChangeConfirm = Confirmable<const StateElement &, State, State, bool>;
  
  public:
    using Observer    = StateChangeNotif  ::Listener;
    using ObserverID  = StateChangeNotif  ::ListenerID;
    using Confirmer   = StateChangeConfirm::Listener;
    using ConfirmerID = StateChangeConfirm::ListenerID;
    
    class StateError final : public std::runtime_error {
    public:
      explicit StateError(const char *);
    };
    
    explicit StateElement(const std::string &, SubState = 1, SubState = 0);
    ~StateElement() = default;
    
    ObserverID addObserver(const Observer &);
    void remObserver(ObserverID);
    ConfirmerID addConfirmer(const Confirmer &);
    void remConfirmer(ConfirmerID);
    
    void setSubState(SubState);
    SubState getSubState() const;
    
  private:
    StateChangeNotif stateChangeNotif;
    StateChangeConfirm stateChangeConfirm;
    State state;
    SubState numSubStates;
    
    void changeButtonState(ButtonState);
    void changeSubState(SubState, bool = false);
    void changeState(State, bool = false);
    SubState nextSubState() const;
    
    void onMouseDown() override final;
    void onMouseUp(bool) override final;
    void onMouseEnter(bool) override final;
    void onMouseLeave(bool) override final;
  };
}

#endif
