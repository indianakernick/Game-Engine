//
//  geometry3d.cpp
//  game engine
//
//  Created by Indi Kernick on 24/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "geometry3d.hpp"

/*using namespace D3;

Geometry::Geometry(int vert, int face)
  : verts(vert), vertsDouble(verts.buf), faces(face * 3) {
  
}

Geometry Geometry::makeCube() {
  static const double verts[24] {
     0.5, 0.5, 0.5,
     0.5, 0.5,-0.5,
     0.5,-0.5, 0.5,
     0.5,-0.5,-0.5,
    -0.5, 0.5, 0.5,
    -0.5, 0.5,-0.5,
    -0.5,-0.5, 0.5,
    -0.5,-0.5,-0.5
  };
  //anticlockwise winding
  static const int faces[36] {
    //+z
    4,6,2,
    2,0,4,
    //+x
    0,2,3,
    3,1,0,
    //-z
    1,3,7,
    7,5,1,
    //-x
    5,7,6,
    6,4,5,
    //+y
    5,4,0,
    0,1,5,
    //-y
    6,7,3,
    3,2,6
  };

  Geometry out(8,12);
  out.vertsDouble.copy(verts, 24);
  out.faces.copy(faces, 36);
  return out;
}

Geometry Geometry::makeCylinder(int vertices) {
  Geometry out(vertices * 2 + 2, vertices * 4);
  
  double deltaAngle = Math::PIt2 / vertices;
  
  /*
  i split the verts array into two separate arrays
  the first half is the vertices that make up the +y face
  and the second half is the -y face.
  after these two arrays are the centers
  +y is at vertices * 2 and -y is at vertices * 2 + 1
  /
  
  for (int i = 0; i < vertices; i++) {
    double x = cos(deltaAngle * i) / 2;
    double y = sin(deltaAngle * i) / 2;
    out.verts[i           ] = {x,  0.5, y};
    out.verts[i + vertices] = {x, -0.5, y};
    
    //anti clockwise winding
    
    //+y face
    out.faces[i * 12 + 0] = (i - 1 + vertices) % vertices;//last
    out.faces[i * 12 + 1] = i;//this
    out.faces[i * 12 + 2] = vertices * 2;//center
    //-y face
    out.faces[i * 12 + 3] = i + vertices;//this
    out.faces[i * 12 + 4] = (i - 1 + vertices) % vertices + vertices;//last
    out.faces[i * 12 + 5] = vertices * 2 + 1;//center
    //side face with base on +y
    out.faces[i * 12 + 6] = i;//this
    out.faces[i * 12 + 7] = (i - 1 + vertices) % vertices;//last
    out.faces[i * 12 + 8] = (i - 1 + vertices) % vertices + vertices;//this -y
    //side face with base on -y
    out.faces[i * 12 + 9] = i;//this
    out.faces[i * 12 +10] = i + vertices;//this -y
    out.faces[i * 12 +11] = (i - 1 + vertices) % vertices + vertices;//last -y
  }
  //centers
  out.verts[vertices * 2 + 0] = {0, 0.5,0};
  out.verts[vertices * 2 + 1] = {0,-0.5,0};
  
  return out;
}

Geometry Geometry::makeCone(int vertices) {
  Geometry out(vertices + 2, vertices * 2);
  
  double deltaAngle = Math::PIt2 / vertices;
  
  //the vertices array is -y faces, center of -y, apex
  
  for (int i = 0; i < vertices; i++) {
    double x = cos(deltaAngle * i) / 2;
    double y = sin(deltaAngle * i) / 2;
    out.verts[i] = {x, -0.5, y};
    
    //-y face
    out.faces[i * 6 + 0] = i;//this
    out.faces[i * 6 + 1] = (i - 1 + vertices) % vertices;//last
    out.faces[i * 6 + 2] = vertices + 1;//center
    //side face
    out.faces[i * 6 + 3] = i;//this
    out.faces[i * 6 + 4] = vertices;//apex
    out.faces[i * 6 + 5] = (i - 1 + vertices) % vertices;//last
  }
  //center
  out.verts[vertices + 0] = {0,-0.5,0};
  //apex
  out.verts[vertices + 1] = {0, 0.5,0};
  
  return out;
}*/