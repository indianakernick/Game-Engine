//
//  radio.hpp
//  Game Engine
//
//  Created by Indi Kernick on 25/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_radio_hpp
#define engine_game_view_human_radio_hpp

#include "element.hpp"
#include <functional>

namespace UI {
  ///Similar to checkbox but mutually exclusive with its sibling radios
  class Radio final : public Element {
  public:
    using Ptr = std::shared_ptr<Radio>;
    using Listener = std::function<void (Radio &)>;
    
    struct Textures {
      std::string unCheckOut;
      std::string unCheckHover;
      std::string unCheckDown;
      
      std::string checkOut;
      std::string checkHover;
      std::string checkDown;
    };
    
    Radio() = default;
    explicit Radio(bool checked);
    ~Radio() = default;
    
    void onCheck(const Listener &);
    void onUncheck(const Listener &);
    
    void setTextures(const Textures &);
    const Textures &getTextures() const;
    const std::string &getTexture() const override;
  
  private:
    enum class State : uint8_t {
      UNCHECK_DOWN_OUT,
      UNCHECK_OUT,
      UNCHECK_HOVER,
      UNCHECK_DOWN,
      
      CHECK_DOWN_OUT,
      CHECK_OUT,
      CHECK_HOVER,
      CHECK_DOWN
    } state = State::UNCHECK_OUT;
    Listener check = defaultListener;
    Listener uncheck = defaultListener;
    Textures textures;
    
    template <Listener Radio::*>
    void setListener(const Listener &);
    static void defaultListener(Radio &) {}
    
    static bool isChecked(State);
    static State makeCheckedIf(bool, State);
    static State makeUnchecked(State);
    void changeState(State);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
};

#endif
