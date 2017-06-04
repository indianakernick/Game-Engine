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
#include "../../Utils/safe down cast.hpp"

namespace UI {
  class NotifyButtonChange {
  public:
    using Observer = std::function<void (StateElement &)>;
    
    NotifyButtonChange(const Observer &, const Observer &, const Observer &, const Observer &);
    ~NotifyButtonChange() = default;
    
    void operator()(StateElement::StateChange::Ptr) const;
    
  private:
    Observer down, up, enter, leave;
    
    static void defaultObserver(StateElement &) {}
  };
  
  class NotifySubStateChange {
  public:
    using Observer = std::function<void (StateElement &)>;
    
    template <
      typename ...ARGS,
      std::enable_if_t<
          (std::is_convertible<ARGS, Observer>::value && ...) &&
          sizeof...(ARGS) != 0,
        int
      > = 0
    >
    explicit NotifySubStateChange(ARGS &&... args)
      : observers({(args ? std::forward<ARGS>(args) : defaultObserver)...}) {}
    ~NotifySubStateChange() = default;
  
    void operator()(StateElement::StateChange::Ptr) const;
  
  private:
    std::vector<Observer> observers;
    
    static void defaultObserver(StateElement &) {}
  };
  
  class SetTextures {
  public:
    static constexpr size_t NUM_TEX_PER_STATE = 3;
  
    template <
      typename ...ARGS,
      std::enable_if_t<
          (std::is_convertible<ARGS, std::string>::value && ...) &&
          sizeof...(ARGS) % NUM_TEX_PER_STATE == 0 &&
          sizeof...(ARGS) != 0,
        int
      > = 0
    >
    explicit SetTextures(ARGS &&... args)
      : textures({{std::forward<ARGS>(args), {}}...}) {}
    
    template <
      typename ...ARGS,
      std::enable_if_t<
          sizeof...(ARGS) % NUM_TEX_PER_STATE == 0 &&
          sizeof...(ARGS) != 0,
        int
      > = 0
    >
    explicit SetTextures(ARGS &&... args)
      : textures({std::forward<ARGS>(args)...}) {}
    ~SetTextures() = default;
    
    void operator()(StateElement::StateChange::Ptr) const;
    
  private:
    Textures textures;
  };
  
  class SetTexturesButtonState {
  public:
    SetTexturesButtonState(const std::string &, const std::string &, const std::string &);
    SetTexturesButtonState(const Texture &, const Texture &, const Texture &);
    ~SetTexturesButtonState() = default;
    
    void operator()(StateElement::StateChange::Ptr) const;
    
  private:
    Texture out, hover, down;
  };
  
  class SetTexturesSubState {
  public:
    template <
      typename ...ARGS,
      std::enable_if_t<
          (std::is_convertible<ARGS, std::string>::value && ...) &&
          sizeof...(ARGS) != 0,
        int
      > = 0
    >
    explicit SetTexturesSubState(ARGS &&... args)
      : textures({Texture(std::string(std::forward<ARGS>(args)))...}) {}
    
    template <
      typename ...ARGS,
      std::enable_if_t<
          (std::is_convertible<ARGS, Texture>::value && ...) &&
          sizeof...(ARGS) != 0,
        int
      > = 0
    >
    explicit SetTexturesSubState(ARGS &&... args)
      : textures({std::forward<ARGS>(args)...}) {}
    ~SetTexturesSubState() = default;
    
    void operator()(StateElement::StateChange::Ptr) const;
    
  private:
    Textures textures;
  };
}

#endif
