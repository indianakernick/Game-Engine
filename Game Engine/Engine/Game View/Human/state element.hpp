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
#include "../../Utils/member function.hpp"

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
    
    class StateChange final : public Event {
    public:
      using Ptr = std::shared_ptr<StateChange>;
      static const Type TYPE;
      
      StateChange(StateElement &, State, State, bool);
      
      StateElement &element;
      State fromState; //the state the element is transitioning from
      State toState; //the state the element is transitioning to
      bool manual; //whether this state change was triggered by code rather than the user
    };
    
  private:
    using StateChangeConfirm = Confirmable<
      uint32_t,
      StateChange::Ptr
    >;
  
  public:
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
    
    ListenerID addListener(Event::Type, const Listener &) override;
    ConfirmerID addConfirmer(const Confirmer &);
    void remConfirmer(ConfirmerID);
    void setDecider(const Decider &);
    void setDefaultDecider();
    void setNoChangeDecider();
    
    void setSubState(SubState);
    SubState getSubState() const;
    
  private:
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
    
    void onMouseDown(Event::Ptr);
    void onMouseUp(Event::Ptr);
    void onMouseEnter(Event::Ptr);
    void onMouseLeave(Event::Ptr);
  };
}

#endif
