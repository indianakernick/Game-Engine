//
//  image.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_image_hpp
#define engine_game_view_human_image_hpp

#include "element.hpp"

namespace UI {
  ///Simply an image. No states, no callbacks, just an image.
  class Image final : public Element {
  public:
    using Ptr = std::shared_ptr<Image>;
    
    Image() = default;
    ~Image() = default;
    
    void setTexture(const Res::ID &);
    const Res::ID &getTexture() const override;
  
  private:
    Res::ID texture;
    
    void onMouseDown() override {}
    void onMouseUp(bool) override {}
    void onMouseEnter(bool) override {}
    void onMouseLeave(bool) override {}
  };
}

#endif
