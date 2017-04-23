//
//  renderer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "renderer.hpp"

const size_t UI::Renderer::ESTIMATE_NUM_ELEMENTS = 64;
const UI::Height UI::Renderer::MAX_HEIGHT = 1000;

UI::Renderer::Renderer(
  const Ogre::String &name,
  std::weak_ptr<Platform::Window> window,
  Ogre::Viewport *viewport,
  Ogre::SceneManager *sceneManager)
  : window(window), viewport(viewport) {
  assert(viewport);
  assert(sceneManager);
  
  atlas = Res::TextureAtlasManager::getSingleton().load(
    name + ".atlas",
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::TextureAtlas>();
  
  node = sceneManager->getRootSceneNode()->createChildSceneNode();
  manualObject = sceneManager->createManualObject();
  node->attachObject(manualObject);
  manualObject->setRenderQueueGroup(Ogre::RenderQueueGroupID::RENDER_QUEUE_OVERLAY);
  
  manualObject->estimateVertexCount(4 * ESTIMATE_NUM_ELEMENTS);
  manualObject->estimateIndexCount(6 * ESTIMATE_NUM_ELEMENTS);
  manualObject->setDynamic(true);
  manualObject->setUseIdentityProjection(true);
  manualObject->setUseIdentityView(true);
  manualObject->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
  manualObject->setKeepDeclarationOrder(true);
  
  manualObject->begin(name, Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manualObject->position(1.0f, 1.0f, 0.0f);
  manualObject->textureCoord(1.0f, 0.0f);
  manualObject->colour(1.0f, 1.0f, 1.0f, 1.0f);
 
   manualObject->position(-1.0f, 1.0f, 0.0f);
  manualObject->textureCoord(0.0f, 0.0f);
  manualObject->colour(1.0f, 1.0f, 1.0f, 1.0f);
  
  manualObject->position(-1.0f, -1.0f, 0.0f);
  manualObject->textureCoord(0.0f, 1.0f);
  manualObject->colour(1.0f, 1.0f, 1.0f, 1.0f);
  
  manualObject->triangle(0, 1, 2);
  manualObject->end();
  
  Ogre::Root::getSingleton().addFrameListener(this);
}

UI::Renderer::~Renderer() {
  Ogre::Root::getSingleton().removeFrameListener(this);
}

void UI::Renderer::setRoot(Element::Ptr newRoot) {
  assert(newRoot);
  root = newRoot;
}

void UI::Renderer::unSetRoot() {
  root = nullptr;
}

UI::Renderer::DrawObject::DrawObject(
  UI::SimpleAABB newBounds,
  Res::TextureAtlas::Sprite textureCoords,
  glm::vec4 color,
  UI::Height height
) : textureCoords(textureCoords),
    color(color.r, color.g, color.b, color.a),
    depth(1.0f - static_cast<Ogre::Real>(height) / MAX_HEIGHT) {
  bounds.left = newBounds.pos.x * 2.0f - 1.0f;
  bounds.top = (1.0f - newBounds.pos.y) * 2.0f - 1.0f;
  bounds.right = (newBounds.pos.x + newBounds.size.x) * 2.0f - 1.0f;
  bounds.bottom = (1.0f - (newBounds.pos.y + newBounds.size.y)) * 2.0f - 1.0f;
}

bool UI::Renderer::frameStarted(const Ogre::FrameEvent &) {
  if (root == nullptr) {
    return true;
  }
  
  AABBStack aabbStack(getAspectRatio());
  HeightStack heightStack;
  DrawObjects drawObjects;
  fillDrawObjects(aabbStack, atlas, root, heightStack, drawObjects);
  std::sort(drawObjects.begin(), drawObjects.end(), [](const DrawObject &a,
                                                       const DrawObject &b) {
    return a.depth > b.depth;
  });
  fillManualObject(drawObjects);
  
  return true;
}

float UI::Renderer::getAspectRatio() const {
  return static_cast<float>(viewport->getActualWidth()) /
         viewport->getActualHeight();
}

void UI::Renderer::fillDrawObjects(
  UI::AABBStack &aabbStack,
  const Res::TextureAtlasPtr &atlas,
  const UI::Element::Ptr element,
  UI::HeightStack &heightStack,
  DrawObjects &objects
) {
  aabbStack.push(element->getBounds());
  heightStack.push(element->getHeight());
  
  objects.emplace_back(
    aabbStack.top(),
    atlas->getSprite(element->getTexture()),
    element->getColor(),
    heightStack.top()
  );
  
  const UI::Element::Children &children = element->getChildren();
  for (auto i = children.begin(); i != children.end(); i++) {
    fillDrawObjects(aabbStack, atlas, *i, heightStack, objects);
  }
  
  heightStack.pop();
  aabbStack.pop();
}

void UI::Renderer::fillManualObject(const DrawObjects &objects) {
  manualObject->beginUpdate(0);
  
  Ogre::uint32 i = 0;
  for (auto o = objects.begin(); o != objects.end(); o++, i += 4) {
    const DrawObject &obj = *o;
    
    //top left
    manualObject->position(obj.bounds.left, obj.bounds.top, obj.depth);
    manualObject->textureCoord(obj.textureCoords.left, obj.textureCoords.top);
    manualObject->colour(obj.color);
    //bottom left
    manualObject->position(obj.bounds.left, obj.bounds.bottom, obj.depth);
    manualObject->textureCoord(obj.textureCoords.left, obj.textureCoords.bottom);
    manualObject->colour(obj.color);
    //bottom right
    manualObject->position(obj.bounds.right, obj.bounds.bottom, obj.depth);
    manualObject->textureCoord(obj.textureCoords.right, obj.textureCoords.bottom);
    manualObject->colour(obj.color);
    //top right
    manualObject->position(obj.bounds.right, obj.bounds.top, obj.depth);
    manualObject->textureCoord(obj.textureCoords.right, obj.textureCoords.top);
    manualObject->colour(obj.color);
    
    manualObject->quad(i, i + 1, i + 2, i + 3);
  }
  manualObject->end();
}
