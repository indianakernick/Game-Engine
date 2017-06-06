//
//  xml.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_managers_xml_hpp
#define engine_resource_managers_xml_hpp

#include "../Handles/xml.hpp"

namespace Res {
  class XMLManager final : public Ogre::ResourceManager,
                           public Ogre::Singleton<XMLManager> {
  public:
    XMLManager();
    ~XMLManager();
    
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
