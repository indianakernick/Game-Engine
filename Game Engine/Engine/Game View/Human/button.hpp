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
#include "../../Resource/id.hpp"

namespace UI {
  class Button : public Element {
  friend class Input;
  public:
    using Ptr = std::shared_ptr<Button>;
  
    enum State : uint8_t {
      //the mouse is down but not within the bounds of the button
      DOWN_OUT,
      OUT,
      HOVER,
      DOWN
    };
    
    struct Textures {
      Res::ID out;
      Res::ID hover;
      Res::ID down;
    };
    
    using Listener = std::function<void (Button &)>;
    //using Listener = void (*)(Button *);
    
    Button() = default;
    ~Button() = default;
    
    void onDown(Listener);
    void onUp(Listener);
    void onEnter(Listener);
    void onLeave(Listener);
    
    void setTextures(const Textures &);
    const Textures &getTextures() const;
    const Res::ID &getTexture() const override;
    
  private:
    State state = OUT;
    Listener down = defaultListener;
    Listener up = defaultListener;
    Listener enter = defaultListener;
    Listener leave = defaultListener;
    Textures textures;
    
    template <Listener Button::*>
    void setListener(const Listener &);
    
    void changeState(State);
    
    static void defaultListener(Button &) {};
    
    void onMouseDown() override;
    void onMouseUp(bool) override;
    void onMouseEnter(bool) override;
    void onMouseLeave(bool) override;
  };
}

#endif
