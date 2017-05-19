//
//  ui screen.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_ui_screen_hpp
#define engine_resource_handles_ui_screen_hpp

#include "../../Application/ogre.pch"
#include "../../Game View/Human/element.hpp"

namespace Res {
  class UIScreen final : public Ogre::Resource {
  friend class UIScreenSerializer;
  public:
    using Ptr = Ogre::SharedPtr<UIScreen>;
  
    UIScreen(
      Ogre::ResourceManager *,
      const Ogre::String &,
      Ogre::ResourceHandle,
      const Ogre::String &,
      bool,
      Ogre::ManualResourceLoader *
    );
    ~UIScreen();
    
    UI::Element::Ptr getRoot() const;
    const std::string &getScreenName() const;
    
  private:
    UI::Element::Ptr root;
    std::string name;
  
    void loadImpl() override;
    void unloadImpl() override;
    size_t calculateSize() const override;
  };
}

#endif
