//
//  ui screen.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_serializers_ui_screen_hpp
#define engine_resource_serializers_ui_screen_hpp

#include "../Handles/ui screen.hpp"
#include <tinyxml2.h>
#include "../exceptions.hpp"
#include "../../Utils/string enum.hpp"
#include "../../Game View/Human/button.hpp"
#include "../../Game View/Human/image.hpp"
#include "../../Game View/Human/checkbox.hpp"
#include "../../Game View/Human/radio.hpp"
#include "../../Game View/Human/caption.hpp"
#include "../../Game View/Human/paragraph.hpp"

namespace Res {
  class InvalidUIScreen final : public InvalidResource {
  public:
    explicit InvalidUIScreen(const std::string &);
  };

  class UIScreenSerializer final : public Ogre::Serializer {
  public:
    UIScreenSerializer() = default;
    ~UIScreenSerializer() = default;
    
    void importScreen(Ogre::DataStreamPtr &, UIScreen *);
  };
}

#endif
