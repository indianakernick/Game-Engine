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

namespace UI {
  ///A checkbox which is either checked or not checked
  class Checkbox final : public Element {
  public:
    using Ptr = std::shared_ptr<Checkbox>;
    using Listener = std::function<void (Checkbox &)>;
    
    struct Textures {
      Res::ID unCheckOut;
      Res::ID unCheckHover;
      Res::ID unCheckDown;
      
      Res::ID checkOut;
      Res::ID checkHover;
      Res::ID checkDown;
    };
    
    Checkbox() = default;
    ~Checkbox() = default;
    
    void onCheck(const Listener &);
    void onUncheck(const Listener &);
    
    void setTextures(const Textures &);
    const Textures &getTextures() const;
    const Res::ID &getTexture() const override;
  
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
    
    template <Listener Checkbox::*>
    void setListener(const Listener &);
    static void defaultListener(Checkbox &) {}
    
    static bool isChecked(State);
    static State makeCheckedIf(bool, State);
    void changeState(State);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
};

#endif
