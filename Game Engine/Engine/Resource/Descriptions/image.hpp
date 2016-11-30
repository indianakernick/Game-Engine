//
//  image.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_descriptions_image_hpp
#define engine_resource_descriptions_image_hpp

#include "../desc.hpp"
#include "../../Geometry/size.hpp"

namespace Resource {
  namespace Descs {
    class Image : public Desc {
    public:
      Image(Geometry::Size size, int depth);
      
      Geometry::Size getSize();
      int getDepth();
    private:
      const Geometry::Size size;
      const int depth;
    };
  }
}

#endif
