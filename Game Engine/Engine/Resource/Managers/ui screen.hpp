//
//  ui screen.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_managers_ui_screen_hpp
#define engine_resource_managers_ui_screen_hpp

#include "../Handles/ui screen.hpp"

namespace Res {
  class UIScreenManager final : public Ogre::ResourceManager,
                                public Ogre::Singleton<UIScreenManager> {
  public:
    UIScreenManager();
    ~UIScreenManager();
    
  private:
    Ogre::Resource *createImpl(
      const Ogre::String &,
      Ogre::ResourceHandle,
      const Ogre::String &,
      bool,
      Ogre::ManualResourceLoader *,
      const Ogre::NameValuePairList *
    ) override;
  };
}

#endif
