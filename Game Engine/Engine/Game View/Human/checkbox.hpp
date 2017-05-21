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
#include "../../Utils/observable.hpp"

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
  
  private:
    using StateChange = Observable<bool (Checkbox &, State, State, bool)>;
  
  public:
    using Listener = StateChange::Listener;
    using ListenerID = StateChange::ListenerID;
    
    class CallListeners {
    public:
      using Listener = std::function<void (Checkbox &)>;
      
      CallListeners(const Listener &, const Listener &);
      
      bool operator()(Checkbox &, State, State, bool) const;
    
    private:
      Listener unCheck, check;
      
      static void defaultListener(Checkbox &) {}
    };
    
    class SetTextures {
    private:
      using StringRef = const std::string &;
      
    public:
      SetTextures(StringRef, StringRef, StringRef, StringRef, StringRef, StringRef);
      
      bool operator()(Checkbox &, State, State, bool) const;
      
    private:
      std::string unCheckOut, unCheckHover, unCheckDown,
                  checkOut, checkHover, checkDown;
    };
    
    class Radio {
    public:
      Radio() = default;
      
      bool operator()(Checkbox &, State, State, bool) const;
    };
    
    explicit Checkbox(const std::string &, bool = false);
    ~Checkbox() = default;
  
    ListenerID addStateChangeListener(const Listener &);
    void remStateChangeListener(ListenerID);
    bool isChecked() const;
    void check();
    void uncheck();
    
    static bool isChecked(State);
  
  private:
    StateChange stateChange;
    State state = State::UNCHECK_OUT;
    
    static void defaultListener(Checkbox &, State, State) {}
    static State makeCheckedIf(bool, State);
    static State makeChecked(State);
    static State makeUnchecked(State);
    void changeState(State, bool = false);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
};

#endif
