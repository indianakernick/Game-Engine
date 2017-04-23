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
  class Caption final : public Element {
  public:
    using Ptr = std::shared_ptr<Caption>;
    
    Caption() = default;
    ~Caption() = default;
    
    void setFont(const std::string &);
    void setText(const std::string &);
    
    const std::string &getFont() const;
    const std::string &getText() const;
    
    const std::string &getTexture() const override;
  
  private:
    std::string font;
    //English text is stored. International text is looked up in app->strings
    std::string text;
    
    static const std::string EMPTY_STRING;
    
    void onMouseDown() override {}
    void onMouseUp(bool) override {}
    void onMouseEnter(bool) override {}
    void onMouseLeave(bool) override {}
  };
}

#endif
