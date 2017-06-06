//
//  xml.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_xml_hpp
#define engine_resource_handles_xml_hpp

#include "../../Application/ogre.hpp"
#include <tinyxml2.h>

namespace Res {
  class XML final : public Ogre::Resource {
  friend class XMLSerializer;
  public:
    using Ptr = Ogre::SharedPtr<XML>;
  
    XML(
      Ogre::ResourceManager *,
      const Ogre::String &,
      Ogre::ResourceHandle,
      const Ogre::String &,
      bool,
      Ogre::ManualResourceLoader *
    );
    ~XML();
    
    const tinyxml2::XMLDocument *getDocument() const;
    const tinyxml2::XMLElement *getRoot() const;
    
  private:
    std::unique_ptr<tinyxml2::XMLDocument> document;
    tinyxml2::XMLElement *root;
  
    void loadImpl() override;
    void unloadImpl() override;
    size_t calculateSize() const override;
  };
}

#endif
