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
    using StateChangeNotif   = Observable <
      uint32_t, //listener ID
      StateElement &,
      State, //the state the element is transitioning from
      State  //the state the element is transitioning to
    >;
    using StateChangeConfirm = Confirmable<
      uint32_t, //listener ID
      const StateElement &,
      State, //the state the element is transitioning from
      State, //the state the element is transitioning to
      bool   //whether this state change was triggered by code rather than the user
    >;
  
  public:
    ///Observes state changes
    using Observer    = StateChangeNotif  ::Listener;
    using ObserverID  = StateChangeNotif  ::ListenerID;
    ///Confirms that this state change should happen
    using Confirmer   = StateChangeConfirm::Listener;
    using ConfirmerID = StateChangeConfirm::ListenerID;
    ///Decides which substate to transition into
    using Decider = std::function<SubState (
      SubState, //the current sub state
      SubState  //the number of sub states
    )>;
    
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
    void setDecider(const Decider &);
    void setDefaultDecider();
    void setNoChangeDecider();
    
    void setSubState(SubState);
    SubState getSubState() const;
    
  private:
    StateChangeNotif stateChangeNotif;
    StateChangeConfirm stateChangeConfirm;
    Decider decider = defaultDecider;
    State state;
    SubState numSubStates;
    
    void changeButtonState(ButtonState);
    void changeSubState(SubState, bool = false);
    void changeState(State, bool = false);
    SubState nextSubState() const;
    
    static SubState defaultDecider(SubState, SubState);
    static SubState noChangeDecider(SubState, SubState);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
}

#endif
