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
      DEFAULT,
      HOVER,
      DOWN
    };
    
    struct Textures {
      Res::ID def;
      Res::ID hover;
      Res::ID down;
    };
    
    using Listener = std::function<void (Button *)>;
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
    State state = DEFAULT;
    Listener down = defaultListener;
    Listener up = defaultListener;
    Listener enter = defaultListener;
    Listener leave = defaultListener;
    Textures textures;
    
    void changeState(State);
    
    static void defaultListener(Button *) {};
  };
}

#endif
