//
//  triangulate.cpp
//  Game Engine
//
//  Created by Indi Kernick on 31/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "triangulate.hpp"

uint32_t Triangulate::mesh(uint32_t *polyI, uint32_t *polySize, uint32_t polyNum, uint32_t *triI) {
  //the current index of the polyI array. the index of the first element of the
  //polygon subarray
  uint32_t polyIndex = 0;
  //after the outer for-loop it will be the number of triangles in the
  //resulting mesh but in the for-loop it is used as triIndex
  uint32_t triNum = 0;
  for (uint32_t i = 0; i < polyNum; i++) {
    //number of vertices in the triangle mesh that makes up the current polygon
    uint32_t verts = polyTriCount(polySize[i]) * 3;
    //j is the current vertex in the triangle mesh
    for (uint32_t j = 0; j < verts; j++) {
      triI[triNum + j] = polyI[magic(polySize[i], j) + polyIndex];
    }
    triNum += polyTriCount(polySize[i]);
    polyIndex += polySize[i];
  }
  return triNum;
}

uint32_t Triangulate::mesh(uint32_t *polyI, uint32_t polySize, uint32_t polyNum, uint32_t *triI) {
  //number of triangles in the resulting mesh
  uint32_t triNum = polyTriCount(polySize);
  //number of vertices in the resulting mesh
  const uint32_t verts = triNum * 3;
  //number of vertices in the polygon mesh
  const uint32_t polyVerts = polyNum * polySize;
  //current index on the triI array
  uint32_t triIndex = 0;
  for (uint32_t i = 0; i < polyVerts; i+=polySize) {
    //j is the current vertex in the triangle mesh
    for (uint32_t j = 0; j < verts; j++) {
      triI[triIndex + j] = polyI[magic(polySize, j) + i];
    }
    triIndex += verts;
  }
  return triNum;
}

uint32_t Triangulate::poly(uint32_t *polyI, uint32_t polySize, uint32_t *triI) {
  const uint32_t verts = polyVertCount(polySize);
  for (uint32_t i = 0; i < verts; i++) {
    triI[i] = polyI[magic(polySize, i)];
  }
  return polyTriCount(polySize);
}

uint32_t Triangulate::poly(uint32_t polySize, uint32_t *triI) {
  const uint32_t verts = polyVertCount(polySize);
  for (uint32_t i = 0; i < verts; i++) {
    triI[i] = magic(polySize, i);
  }
  return polyTriCount(polySize);
}

uint32_t Triangulate::meshTriCount(uint32_t *polySize, uint32_t polyNum) {
  uint32_t size = 0;
  for (uint32_t i = 0; i < polyNum; i++) {
    size += polyTriCount(polySize[i]);
  }
  return size;
}

uint32_t Triangulate::meshVertCount(uint32_t *polySize, uint32_t polyNum) {
  return meshTriCount(polySize, polyNum) * 3;
}
