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
#include "../../Utils/dispatcher.hpp"

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
    using StateChangeNotif = Observable<Checkbox &, State, State>;
    using StateChangeConfirm = Confirmable<Checkbox &, State, State, bool>;
  
  public:
    using Observer = StateChangeNotif::Listener;
    using ObserverID = StateChangeNotif::ListenerID;
    //There should be a stack exchange site dedicated to naming things
    using Confirmer = StateChangeConfirm::Listener;
    using ConfirmerID = StateChangeConfirm::ListenerID;
    
    class NotifyObservers {
    public:
      using Observer = std::function<void (Checkbox &)>;
      
      NotifyObservers(const Observer &, const Observer &);
      
      void operator()(Checkbox &, State, State) const;
    
    private:
      Observer unCheck, check;
      
      static void defaultObserver(Checkbox &) {}
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
    
    class RadioObserver {
    public:
      RadioObserver() = default;
      
      void operator()(Checkbox &, State, State) const;
    };
    
    class RadioConfirmer {
    public:
      RadioConfirmer() = default;
      
      bool operator()(Checkbox &, State, State, bool) const;
    };
    
    explicit Checkbox(const std::string &, bool = false);
    ~Checkbox() = default;
  
    ObserverID addObserver(const Observer &);
    void remObserver(ObserverID);
    ConfirmerID addConfirmer(const Confirmer &);
    void remConfirmer(ConfirmerID);
    
    bool isChecked() const;
    void check();
    void uncheck();
    
    static bool isChecked(State);
  
  private:
    StateChangeNotif stateChangeNotif;
    StateChangeConfirm stateChangeConfirm;
    State state = State::UNCHECK_OUT;
    
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
