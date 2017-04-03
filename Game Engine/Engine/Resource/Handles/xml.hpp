//
//  xml.hpp
//  Game Engine
//
//  Created by Indi Kernick on 3/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_descriptions_xml_hpp
#define engine_resource_descriptions_xml_hpp

#include "../handle.hpp"
#include "../../../Libraries/tinyxml2.hpp"

namespace Res {
  class XML final : public Handle {
  public:
    using Ptr = std::shared_ptr<XML>;
  
    XML(std::shared_ptr<tinyxml2::XMLDocument> document);
    
    const tinyxml2::XMLDocument &getDoc() const;
    const tinyxml2::XMLElement &getRoot() const;
  private:
    std::shared_ptr<tinyxml2::XMLDocument> document;
  };
}

#endif
