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

namespace UI {
  class Button : public Element {
  public:
    using Ptr = std::shared_ptr<Button>;
    using Listener = std::function<void (Button &)>;
    
    struct Textures {
      Res::ID out;
      Res::ID hover;
      Res::ID down;
    };
    
    Button() = default;
    ~Button() = default;
    
    void onDown(const Listener &);
    void onUp(const Listener &);
    void onEnter(const Listener &);
    void onLeave(const Listener &);
    
    void setTextures(const Textures &);
    const Textures &getTextures() const;
    const Res::ID &getTexture() const override;
    
  private:
    enum class State : uint8_t {
      DOWN_OUT,
      OUT,
      HOVER,
      DOWN
    } state = State::OUT;
    Listener down = defaultListener;
    Listener up = defaultListener;
    Listener enter = defaultListener;
    Listener leave = defaultListener;
    Textures textures;
    
    template <Listener Button::*>
    void setListener(const Listener &);
    static void defaultListener(Button &) {};
    
    void changeState(State);
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
}

#endif
