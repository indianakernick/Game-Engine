//
//  event.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_event_hpp
#define engine_input_event_hpp

#include "State/mouse.hpp"
#include "State/keyboard.hpp"
#include "../Event/event.hpp"
#include "../Event/type gen.hpp"
#include <glm/vec2.hpp>
#include "../Platform/Interface/window.hpp"

namespace Input {
  class MouseDown final : public Game::Event {
  public:
    using Ptr = std::shared_ptr<MouseDown>;
    static const Type TYPE;
    
    std::weak_ptr<Platform::Window> window;
    glm::ivec2 pos;
    MButton::Type button;
    int repeat;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class MouseUp final : public Game::Event {
  public:
    using Ptr = std::shared_ptr<MouseUp>;
    static const Type TYPE;
    
    std::weak_ptr<Platform::Window> window;
    glm::ivec2 pos;
    MButton::Type button;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class MouseMove final : public Game::Event {
  public:
    using Ptr = std::shared_ptr<MouseMove>;
    static const Type TYPE;
    
    std::weak_ptr<Platform::Window> window;
    glm::ivec2 pos;
    glm::ivec2 delta;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class Scroll final : public Game::Event {
  public:
    using Ptr = std::shared_ptr<Scroll>;
    static const Type TYPE;
    
    std::weak_ptr<Platform::Window> window;
    glm::ivec2 pos;
    glm::ivec2 delta;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class KeyDown final : public Game::Event {
  public:
    using Ptr = std::shared_ptr<KeyDown>;
    static const Type TYPE;
    
    std::weak_ptr<Platform::Window> window;
    Key::Type key;
    Mod::Type modifiers;
    char character;
    bool repeat;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class KeyUp final : public Game::Event {
  public:
    using Ptr = std::shared_ptr<KeyUp>;
    static const Type TYPE;
    
    std::weak_ptr<Platform::Window> window;
    Key::Type key;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class Quit final : public Game::Event {
  public:
    using Ptr = std::shared_ptr<Quit>;
    static const Type TYPE;
    
    Type getType() const override;
    const char *getName() const override;
  };
}

#endif
