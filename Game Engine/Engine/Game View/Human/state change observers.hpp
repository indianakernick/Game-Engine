//
//  state change observers.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_state_change_observers_hpp
#define engine_game_view_human_state_change_observers_hpp

#include "state element.hpp"
#include "../../Utils/combine.hpp"

namespace UI {
  class NotifyButtonChange {
  public:
    using Observer = std::function<void (StateElement &)>;
    
    NotifyButtonChange(const Observer &, const Observer &, const Observer &, const Observer &);
    ~NotifyButtonChange() = default;
    
    void operator()(StateElement &, StateElement::State, StateElement::State);
    
  private:
    Observer down, up, enter, leave;
    
    static void defaultObserver(StateElement &) {}
  };
  
  class NotifySubStateChange {
  public:
    using Observer = std::function<void (StateElement &, StateElement::SubState, StateElement::SubState)>;
    
    explicit NotifySubStateChange(const Observer &);
    ~NotifySubStateChange() = default;
  
    void operator()(StateElement &, StateElement::State, StateElement::State);
  
  private:
    Observer observer;
    
    static void defaultObserver(StateElement &, StateElement::SubState, StateElement::SubState) {}
  };
  
  class SetTextures {
  public:
    static constexpr size_t NUM_TEX_PER_STATE = 3;
  
    explicit SetTextures(StateElement::SubState);
    template <
      typename ...ARGS,
      std::enable_if_t<
          (std::is_convertible<ARGS, std::string>::value && ...) &&
          sizeof...(ARGS) % NUM_TEX_PER_STATE == 0 &&
          sizeof...(ARGS) != 0,
        int
      > = 0
    >
    SetTextures(ARGS &&... args)
      : textures({std::forward<ARGS>(args)...}) {}
    ~SetTextures() = default;
    
    void operator()(StateElement &, StateElement::State, StateElement::State);
    
  private:
    std::vector<std::string> textures;
  };
  
  class SetTexturesButtonState {
  public:
    SetTexturesButtonState(const std::string &, const std::string &, const std::string &);
    ~SetTexturesButtonState() = default;
    
    void operator()(StateElement &, StateElement::State, StateElement::State);
    
  private:
    std::string out, hover, down;
  };
  
  class SetTexturesSubState {
  public:
    explicit SetTexturesSubState(StateElement::SubState numSubStates)
      : textures(numSubStates) {}
    template <
      typename ...ARGS,
      std::enable_if_t<
          (std::is_convertible<ARGS, std::string>::value && ...) &&
          sizeof...(ARGS) != 0,
        int
      > = 0
    >
    SetTexturesSubState(ARGS &&... args)
      : textures({std::forward<ARGS>(args)...}) {}
    ~SetTexturesSubState() = default;
    
    void operator()(StateElement &, StateElement::State, StateElement::State);
    
  private:
    std::vector<std::string> textures;
  };
}

#endif
