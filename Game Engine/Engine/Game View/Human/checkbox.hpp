//
//  checkbox.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_checkbox_hpp
#define engine_game_view_human_checkbox_hpp

#include "element.hpp"
#include <functional>
#include "../../Utils/callable.hpp"

namespace UI {
  ///A checkbox which is either checked or not checked
  class Checkbox final : public Element {
  public:
    using Ptr = std::shared_ptr<Checkbox>;
    
    enum class State : uint8_t {
      UNCHECK_DOWN_OUT,
      UNCHECK_OUT,
      UNCHECK_HOVER,
      UNCHECK_DOWN,
      
      CHECK_DOWN_OUT,
      CHECK_OUT,
      CHECK_HOVER,
      CHECK_DOWN
    };
    
    using ChangeListener = std::function<void (Checkbox &, State, State)>;
    
    class CallListeners {
    public:
      using Listener = std::function<void (Checkbox &)>;
      
      CallListeners(const Listener &, const Listener &);
      
      void operator()(Checkbox &, State, State) const;
    
    private:
      Listener unCheck, check;
      
      static void defaultListener(Checkbox &) {}
    };
    
    class SetTextures {
    private:
      using StringRef = const std::string &;
      
    public:
      SetTextures(StringRef, StringRef, StringRef, StringRef, StringRef, StringRef);
      
      void operator()(Checkbox &, State, State) const;
      
    private:
      std::string unCheckOut, unCheckHover, unCheckDown,
                  checkOut, checkHover, checkDown;
    };
    
    Checkbox() = default;
    explicit Checkbox(bool);
    ~Checkbox() = default;
  
    void onStateChange(const ChangeListener &);
    static bool isChecked(State);
  
  private:
    ChangeListener stateChange = defaultListener;
    State state = State::UNCHECK_OUT;
    
    static void defaultListener(Checkbox &, State, State) {}
    static State makeCheckedIf(bool, State);
    void changeState(State);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
};

template <typename LEFT, typename RIGHT>
std::enable_if_t<
  is_callable_v<LEFT,  UI::Checkbox &, UI::Checkbox::State, UI::Checkbox::State> &&
  is_callable_v<RIGHT, UI::Checkbox &, UI::Checkbox::State, UI::Checkbox::State>,
  UI::Checkbox::ChangeListener
>
operator&&(LEFT left, RIGHT right) {
  return [
    left = UI::Checkbox::ChangeListener(left),
    right = UI::Checkbox::ChangeListener(right)
  ] (
    UI::Checkbox &checkbox,
    UI::Checkbox::State fromState,
    UI::Checkbox::State toState
  ) {
    left(checkbox, fromState, toState);
    right(checkbox, fromState, toState);
  };
}

#endif
