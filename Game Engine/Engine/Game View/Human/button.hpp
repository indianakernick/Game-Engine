//
//  button.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_button_hpp
#define engine_game_view_human_button_hpp

#include "element.hpp"
#include <functional>
#include "../../Utils/combine.hpp"
#include "../../Utils/dispatcher.hpp"

namespace UI {
  class Button final : public Element {
  public:
    using Ptr = std::shared_ptr<Button>;
  
    enum class State : uint8_t {
      DOWN_OUT,
      OUT,
      HOVER,
      DOWN
    };
  
  private:
    using StateChange = Observable<Button &, State, State>;
  
  public:
    using Observer = StateChange::Listener;
    using ObserverID = StateChange::ListenerID;
    
    class NotifyObservers {
    public:
      using Observer = std::function<void (Button &)>;
      
      NotifyObservers(const Observer &, const Observer &, const Observer &, const Observer &);
      
      void operator()(Button &, State, State);
      
    private:
      Observer down, up, enter, leave;
      
      static void defaultObserver(Button &) {}
    };
    
    class SetTextures {
    public:
      SetTextures(const std::string &, const std::string &, const std::string &);
    
      void operator()(Button &, State, State);
      
    private:
      std::string out, hover, down;
    };
    
    explicit Button(const std::string &);
    ~Button() = default;
    
    ObserverID addObserver(const Observer &);
    void remObserver(ObserverID);
    
  private:
    StateChange stateChange;
    State state = State::OUT;
    
    void changeState(State);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
}

#endif
