//
//  coord.cpp
//  game engine
//
//  Created by Indi Kernick on 7/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "transform.hpp"

glm::mat4 Transform::getMat() const {
  //rst rotation scale translation
  glm::mat4 mat = glm::mat4_cast(rot);
  glm::scale(mat, scale);
  return glm::translate(mat, pos);
}
