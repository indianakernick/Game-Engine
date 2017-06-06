//
//  xml.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_serializers_xml_hpp
#define engine_resource_serializers_xml_hpp

#include <tinyxml2.h>
#include "../exceptions.hpp"
#include "../Handles/xml.hpp"

namespace Res {
  class InvalidXMLDocument final : public InvalidResource {
  public:
    explicit InvalidXMLDocument(const std::string &);
  };

  class XMLSerializer final : public Ogre::Serializer {
  public:
    XMLSerializer() = default;
    ~XMLSerializer() = default;
    
    static std::unique_ptr<tinyxml2::XMLDocument> readDocument(const char *, size_t);
    void importDocument(Ogre::DataStreamPtr &, XML *);
  };
}

#endif
