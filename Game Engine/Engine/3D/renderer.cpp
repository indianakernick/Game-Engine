//
//  renderer3d.cpp
//  game engine
//
//  Created by Indi Kernick on 18/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "renderer3d.hpp"

/*D3::Renderer::Renderer(const Graphics::Window& window)
  : window(window) {}

void D3::Renderer::render(const Scene &scene, const Camera &camera) {
  for (auto i = scene.meshs.begin(); i != scene.meshs.end(); ++i) {
    render(i->second, camera);
  }
}

void D3::Renderer::render(const Mesh &mesh, const Camera &camera) {
  Profiler p("Render Mesh");
  const ::Geometry::Size winSize = window.getRect().s;
  SDL_Renderer* renderer = window.getRenderer().get();
  std::vector<SDL_Point> points(mesh.geometry.verts.size());
  Buffer::Float64Bitmap zBuffer(winSize,INFINITY);
  
  const double canX = 3,
               canY = 3;
  
  Mat44 transform;
  mesh.geometry.getMat().mul(camera.getMat().inv(), transform);
  
  for (size_t i = 0; i < mesh.geometry.verts.size(); i++) {
    Profiler p("Iter verts");
    Vec3 camPoint;
    mesh.geometry.verts[i].mul(transform, camPoint);
    if (::Geometry::Point(camPoint.x, camPoint.y).within(zBuffer.getSize())) {
      zBuffer(camPoint.x, camPoint.y) = -camPoint.z;
    }
    
    if (camPoint.z < 0) {
      Vec3 screenPoint{camPoint.x / -camPoint.z,
                       camPoint.y / -camPoint.z,
                       0};
      
      Vec3 ndc{(screenPoint.x + canX / 2) / canX,
                (screenPoint.y + canY / 2) / canY,
                0};
      
      points[i].x = floor(ndc.x * winSize.w);
      points[i].y = floor((1 - ndc.y) * winSize.h);
    }
  }
  
  for (size_t i = 0; i < mesh.geometry.faces.size(); i+=3) {
    Profiler p("Iter faces");
    SDL_Point vertices[4] {
      points[mesh.geometry.faces[i + 0]],
      points[mesh.geometry.faces[i + 1]],
      points[mesh.geometry.faces[i + 2]]
    };
    
    vertices[3] = vertices[0];
    
    SDL_SetRenderDrawColor(renderer, mesh.material.color.r,
                                     mesh.material.color.g,
                                     mesh.material.color.b,
                                     mesh.material.color.a);
    {
    Profiler p("SDL_RenderDrawLines");
    SDL_RenderDrawLines(renderer, vertices, 4);
    }
  }
}

bool D3::Renderer::visible(SDL_Point point) {
  ::Geometry::Size size = window.getRect().s;
  return point.x >= 0 && point.y >= 0 &&
         point.x < size.w && point.y < size.h;
}

void D3::Renderer::clip(SDL_Point points[3], SDL_Point otherPoints[3], bool *usedOther, bool *isVisible) {
  /*
  a triangle is given as input in points
  the other 3 parameters are outputs
  /
  bool visPoints[3] = {
    visible(points[0]),
    visible(points[1]),
    visible(points[2])
  };
  int countVis = visPoints[0] + visPoints[1] + visPoints[2];
  
  //bubble sort
  bool notSorted = true;
  bool sorted = false;
  while (notSorted) {
    sorted = true;
    
    if (visPoints[0] < visPoints[1]) {
      sorted = false;
      std::swap(visPoints[0], visPoints[1]);
      std::swap(points[0], points[1]);
    }
    if (visPoints[1] < visPoints[2]) {
      sorted = false;
      std::swap(visPoints[1], visPoints[2]);
      std::swap(points[1], points[2]);
    }
    
    if (sorted) {
      notSorted = false;
    }
  }
  
  switch(countVis) {
    case 0:
      *isVisible = false;
      *usedOther = false;
      break;
    case 1:
      *isVisible = true;
      *usedOther = false;
      
    case 2:
      *isVisible = true;
      *usedOther = true;
      
    case 3:
      *isVisible = true;
      *usedOther = false;
      break;
  }
}*/