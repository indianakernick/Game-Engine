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
#include "../../Utils/callable.hpp"

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
    
    using ChangeListener = std::function<void (Button &, State, State)>;
    
    class CallListeners {
    public:
      using Listener = std::function<void (Button &)>;
      
      CallListeners(const Listener &, const Listener &, const Listener &, const Listener &);
      
      void operator()(Button &, State, State);
      
    private:
      Listener down, up, enter, leave;
      
      static void defaultListener(Button &) {}
    };
    
    class SetTextures {
    public:
      SetTextures(const std::string &, const std::string &, const std::string &);
    
      void operator()(Button &, State, State);
    private:
      std::string out, hover, down;
    };
    
    Button() = default;
    ~Button() = default;
    
    void onStateChange(const ChangeListener &);
    
  private:
    ChangeListener stateChange = defaultListener;
    State state = State::OUT;
    
    static void defaultListener(Button &, State, State) {}
    
    void changeState(State);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
}

template <typename LEFT, typename RIGHT>
std::enable_if_t<
  is_callable_v<LEFT,  UI::Button &, UI::Button::State, UI::Button::State> &&
  is_callable_v<RIGHT, UI::Button &, UI::Button::State, UI::Button::State>,
  UI::Button::ChangeListener
>
operator&&(LEFT left, RIGHT right) {
  return [
    left = UI::Button::ChangeListener(left),
    right = UI::Button::ChangeListener(right)
  ] (
    UI::Button &button,
    UI::Button::State fromState,
    UI::Button::State toState
  ) {
    left(button, fromState, toState);
    right(button, fromState, toState);
  };
}

#endif
