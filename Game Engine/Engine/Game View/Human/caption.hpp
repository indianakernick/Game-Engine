//
//  caption.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_caption_hpp
#define engine_game_view_human_caption_hpp

#include "element.hpp"
#include "../../Application/base.hpp"

namespace UI {
  ///A short, one line, text caption. Element bounds are calculated from the text
  class Caption : public Element {
  public:
    using Ptr = std::shared_ptr<Caption>;
    
    Caption() = default;
    ~Caption() = default;
    
    void setFont(const Res::ID &);
    void setText(const std::string &);
    
    const Res::ID &getFont() const;
    const std::string &getText() const;
    
    const Res::ID &getTexture() const override;
  
  private:
    Res::ID font;
    //English text is stored. International text is looked up in app->strings
    std::string text;
    
    static const Res::ID NULL_RES_ID;
    
    void onMouseDown() override {}
    void onMouseUp(bool) override {}
    void onMouseEnter(bool) override {}
    void onMouseLeave(bool) override {}
  };
}

#endif
