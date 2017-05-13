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
  ///A short, one line, text caption.
  class Caption final : public Element {
  public:
    using Ptr = std::shared_ptr<Caption>;
    
    Caption() = default;
    ~Caption() = default;
    
    void setFont(const std::string &);
    void setText(const std::string &);
    void setFontSize(FontSize);
    
    const std::string &getFont() const;
    const std::string &getText() const;
    FontSize getFontSize() const;
    
    const std::string &getTexture() const override;
  
  private:
    std::string font;
    std::string text;
    FontSize fontSize = SMALLEST_FONT_SIZE;
    
    static const std::string EMPTY_STRING;
    
    void onMouseDown() override {}
    void onMouseUp(bool) override {}
    void onMouseEnter(bool) override {}
    void onMouseLeave(bool) override {}
  };
}

#endif
