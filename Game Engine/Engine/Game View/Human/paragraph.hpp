//
//  paragraph.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_paragraph_hpp
#define engine_game_view_human_paragraph_hpp

#include "element.hpp"

namespace UI {
  ///A paragraph. Text is wrapped to the bounds and aligned
  class Paragraph final : public Element {
  public:
    using Ptr = std::shared_ptr<Paragraph>;
    
    enum class Align : uint8_t {
      LEFT,
      CENTER,
      RIGHT
    };
    
    Paragraph(const std::string &);
    ~Paragraph() = default;
    
    void setFont(const std::string &);
    void setText(const std::string &);
    void setFontSize(FontSize);
    void setAlign(Align);
    
    const std::string &getFont() const;
    const std::string &getText() const;
    FontSize getFontSize() const;
    Align getAlign() const;
    
  private:
    using Element::setTexture;
  
    std::string font;
    std::string text;
    FontSize fontSize = SMALLEST_FONT_SIZE;
    Align align = Align::LEFT;
    
    void onMouseDown() override {}
    void onMouseUp(bool) override {}
    void onMouseEnter(bool) override {}
    void onMouseLeave(bool) override {}
  };
}

#endif
