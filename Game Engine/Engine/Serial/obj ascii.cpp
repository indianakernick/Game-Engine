//
//  obj ascii.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "obj ascii.hpp"

void ObjASCII::write(std::ofstream &file) {
  for (size_t i = 0; i < verts.size(); i++) {
    file << "v " << verts[i].x << ' ' << verts[i].y << ' ' << verts[i].z << '\n';
  }
  for (size_t i = 0; i < textVerts.size(); i++) {
    file << "vt " << textVerts[i].u << ' ' << textVerts[i].v << ' ' << textVerts[i].w << '\n';
  }
  for (size_t i = 0; i < vertNorms.size(); i++) {
    file << "vn " << vertNorms[i].i << ' ' << vertNorms[i].j << ' ' << vertNorms[i].k << '\n';
  }
  std::string currentMaterial;
  for (auto i = groups.begin(); i != groups.end(); ++i) {
    file << "g " << i->first << '\n';
    std::vector<Face> &faces = i->second.faces;
    for (size_t j = 0; j < faces.size(); j++) {
      if (faces[j].material != currentMaterial) {
        file << "usemtl " << faces[j].material << '\n';
        currentMaterial = faces[j].material;
      }
      bool hasTextVerts = faces[j].textVerts.size();
      bool hasNormals = faces[j].normals.size();
      file << "f ";
      for (size_t k = 0; k < faces[j].verts.size(); k++) {
        file << (faces[j].verts[k] + 1) << '/';
        if (hasTextVerts) {
          file << (faces[j].textVerts[k] + 1);
        }
        file << '/';
        if (hasNormals) {
          file << (faces[j].normals[k] + 1);
        }
        file << '\n';
      }
    }
  }
}
