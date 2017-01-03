//
//  xml.hpp
//  Game Engine
//
//  Created by Indi Kernick on 3/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_xml_hpp
#define engine_resource_loaders_xml_hpp

#include "../loader.hpp"
#include "../../../Libraries/tinyxml2.hpp"
#include "../Descriptions/xml.hpp"

namespace Resource {
  namespace Loaders {
    class XML : public Loader {
    public:
      bool canLoad(const std::string &fileExt) override;
      size_t getSize(const Memory::Buffer file) override;
      bool useRaw() override;
      Desc::Ptr process(const Memory::Buffer file, Memory::Buffer resource) override;
    };
  }
}

#endif
