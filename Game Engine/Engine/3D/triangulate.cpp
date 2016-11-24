//
//  triangulate.cpp
//  Game Engine
//
//  Created by Indi Kernick on 31/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "triangulate.hpp"

Triangulate::uint Triangulate::mesh(uint *polyI, uint *polySize, uint polyNum, uint *triI) {
  //the current index of the polyI array. the index of the first element of the
  //polygon subarray
  uint polyIndex = 0;
  //after the outer for-loop it will be the number of triangles in the
  //resulting mesh but in the for-loop it is used as triIndex
  uint triNum = 0;
  for (uint i = 0; i < polyNum; i++) {
    //number of vertices in the triangle mesh that makes up the current polygon
    uint verts = polyTriCount(polySize[i]) * 3;
    //j is the current vertex in the triangle mesh
    for (uint j = 0; j < verts; j++) {
      triI[triNum + j] = polyI[magic(polySize[i], j) + polyIndex];
    }
    triNum += polyTriCount(polySize[i]);
    polyIndex += polySize[i];
  }
  return triNum;
}

Triangulate::uint Triangulate::mesh(uint *polyI, uint polySize, uint polyNum, uint *triI) {
  //number of triangles in the resulting mesh
  uint triNum = polyTriCount(polySize);
  //number of vertices in the resulting mesh
  const uint verts = triNum * 3;
  //number of vertices in the polygon mesh
  const uint polyVerts = polyNum * polySize;
  //current index on the triI array
  uint triIndex = 0;
  for (uint i = 0; i < polyVerts; i+=polySize) {
    //j is the current vertex in the triangle mesh
    for (uint j = 0; j < verts; j++) {
      triI[triIndex + j] = polyI[magic(polySize, j) + i];
    }
    triIndex += verts;
  }
  return triNum;
}

Triangulate::uint Triangulate::poly(uint *polyI, uint polySize, uint *triI) {
  const uint verts = polyVertCount(polySize);
  for (uint i = 0; i < verts; i++) {
    triI[i] = polyI[magic(polySize, i)];
  }
  return polyTriCount(polySize);
}

Triangulate::uint Triangulate::poly(uint polySize, uint *triI) {
  const uint verts = polyVertCount(polySize);
  for (uint i = 0; i < verts; i++) {
    triI[i] = magic(polySize, i);
  }
  return polyTriCount(polySize);
}

Triangulate::uint Triangulate::meshTriCount(uint *polySize, uint polyNum) {
  uint size = 0;
  for (uint i = 0; i < polyNum; i++) {
    size += polyTriCount(polySize[i]);
  }
  return size;
}

Triangulate::uint Triangulate::meshVertCount(uint *polySize, uint polyNum) {
  return meshTriCount(polySize, polyNum) * 3;
}
