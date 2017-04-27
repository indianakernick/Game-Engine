//
//  renderer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "renderer.hpp"

const size_t UI::Renderer::ESTIMATE_NUM_ELEMENTS = 64;
//MAX_HEIGHT should be a power of two
const UI::Height UI::Renderer::MAX_HEIGHT = 1024;

UI::Renderer::Renderer(
  const Ogre::String &name,
  std::weak_ptr<Platform::Window> window,
  Ogre::Viewport *viewport,
  Ogre::SceneManager *sceneManager)
  : window(window), viewport(viewport), defaultMaterial(name) {
  assert(viewport);
  assert(sceneManager);
  
  atlas = Res::TextureAtlasManager::getSingleton().load(
    name + ".atlas",
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::TextureAtlas>();
  
  assert(atlas->getType() == Res::TextureAtlas::Type::IMAGE);
  
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
  
  addSection(defaultMaterial);
  
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

UI::Renderer::Quad::Quad(
  UI::SimpleAABB newBounds,
  Res::TextureAtlas::Sprite textureCoords,
  UI::Color color,
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
  PROFILE(UI::Renderer::frameStarted);

  if (root == nullptr) {
    return true;
  }
  
  AABBStack aabbStack(getAspectRatio());
  HeightStack heightStack;
  Groups groups;
  groups.push_back({{}, defaultMaterial, false});
  {
    //invoking the profiler in a recursive function is not a good idea!
    PROFILE(UI::Renderer::fillGroups);
    fillGroups(aabbStack, root, heightStack, groups);
  }
  sortGroups(groups);
  fillManualObject(groups);
  
  return true;
}

float UI::Renderer::getAspectRatio() const {
  return static_cast<float>(viewport->getActualWidth()) /
         viewport->getActualHeight();
}

void UI::Renderer::fillGroups(
  UI::AABBStack &aabbStack,
  const UI::Element::Ptr element,
  UI::HeightStack &heightStack,
  Groups &groups
) {
  aabbStack.push(element->getBounds());
  heightStack.push(element->getHeight());
  
  Caption::Ptr caption = std::dynamic_pointer_cast<Caption>(element);
  if (caption) {
    const std::string &font = caption->getFont();
    const std::string &text = caption->getText();
    if (font.size() && text.size()) {
      groups.push_back({{}, font, true});
      fillQuads(
        font,
        text,
        aabbStack.top(),
        heightStack.top(),
        element->getColor(),
        groups.back().quads
      );
      groups.push_back({{}, defaultMaterial, false});
    }
  } else {
    groups.back().quads.emplace_back(
      aabbStack.top(),
      atlas->getSprite(element->getTexture()),
      element->getColor(),
      heightStack.top()
    );
  }
  
  const UI::Element::Children &children = element->getChildren();
  for (auto i = children.begin(); i != children.end(); i++) {
    fillGroups(aabbStack, *i, heightStack, groups);
  }
  
  heightStack.pop();
  aabbStack.pop();
}

void UI::Renderer::fillQuads(
  const std::string &font,
  const std::string &text,
  SimpleAABB bounds,
  Height height,
  Color color,
  Quads &quads
) {
  PROFILE(UI::Renderer::fillQuads);

  Res::TextureAtlasPtr atlas = Res::TextureAtlasManager::getSingleton().load(
    font + ".atlas",
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::TextureAtlas>();
  
  assert(atlas->getType() == Res::TextureAtlas::Type::FONT);
  
  glm::vec2 origin = bounds.pos;
  const glm::vec2 screenSize = {
    viewport->getActualWidth(),
    viewport->getActualHeight()
  };
  
  for (auto c = text.cbegin(); c != text.cend(); c++) {
    if (*c == '\n') {
      origin.x = bounds.pos.x;
      origin.y += atlas->getLineHeight() / screenSize.y;
      continue;
    }
    Res::TextureAtlas::Glyph glyph = atlas->getGlyph(*c);
    quads.push_back({
      {
        {
          origin.x + static_cast<float>(glyph.metrics.bearing.x) / screenSize.x,
          origin.y - static_cast<float>(glyph.metrics.bearing.y) / screenSize.y
        },
        static_cast<glm::vec2>(glyph.metrics.size) / screenSize
      },
      glyph.glyph,
      color,
      height
    });
    origin.x += glyph.metrics.advance / screenSize.x;
    if (c + 1 != text.cend()) {
      origin.x += atlas->getKerning(*c, *(c+1)) / screenSize.x;
    }
  }
}

//Sort the quads from deepest to heighest
void UI::Renderer::sortQuads(Quads &quads) {
  PROFILE(UI::Renderer::sortQuads);
  
  std::sort(
    quads.begin(),
    quads.end(),
    [] (const Quad &a, const Quad &b) {
      return a.depth > b.depth;
    }
  );
}

UI::Renderer::GroupPtrsPair UI::Renderer::partionGroups(Groups &groups) {
  PROFILE(UI::Renderer::partionGroups);

  GroupPtrsPair pair;
  
  for (auto g = groups.begin(); g != groups.end(); g++) {
    if (g->sameDepth) {
      pair.text.push_back(&(*g));
    } else {
      pair.quad.push_back(&(*g));
    }
  }
  
  return pair;
}

void UI::Renderer::sortGroupPair(GroupPtrsPair &pair) {
  PROFILE(UI::Renderer::sortGroupPair);

  for (auto g = pair.quad.begin(); g != pair.quad.end(); g++) {
    sortQuads((*g)->quads);
  }
  
  std::sort(pair.text.begin(), pair.text.end(), [](Group *a, Group *b) {
    return a->quads[0].depth > b->quads[0].depth;
  });
}

UI::Renderer::QuadIters UI::Renderer::getDeepestQuadIters(const GroupPtrs &quadGroups) {
  PROFILE(UI::Renderer::getDeepestQuadIters);

  QuadIters deepestQuads;
  for (auto g = quadGroups.cbegin(); g != quadGroups.cend(); g++) {
    deepestQuads.push_back((*g)->quads.cbegin());
  }
  return deepestQuads;
}

//Search the groups for the deepest quad
UI::Renderer::QuadIterRef UI::Renderer::getDeepestQuad(
  std::vector<QuadIter> &deepestQuads,
  const GroupPtrs &quadGroups
) {
  PROFILE(UI::Renderer::getDeepestQuad);

  /*
  deepestQuads stores an iterator for each group. The iterator points to the
  next deepest quad. This function compares the depth of all the quads pointed
  to by the iterators and returns a reference to the iterator of the deepest one.
  
  This is kind of like merge sort with a variable number of input arrays
  */

  QuadIterRef deepestQuad;
  for (size_t g = 0; g != quadGroups.size(); g++) {
    if (deepestQuads[g] == quadGroups[g]->quads.cend()) {
      continue;
    } else if (!deepestQuad.valid || deepestQuads[g]->depth >= deepestQuad.iter->depth) {
      deepestQuad.iter = deepestQuads[g];
      deepestQuad.groupIndex = g;
      deepestQuad.valid = true;
    }
  }
  return deepestQuad;
}

void UI::Renderer::sortGroups(Groups &groups) {
  PROFILE(UI::Renderer::sortGroups);

  if (groups.size() == 1) {
    if (!groups[0].sameDepth) {
      sortQuads(groups[0].quads);
    }
    return;
  } else if (groups.size() == 0) {
    return;
  }

  GroupPtrsPair pair = partionGroups(groups);
  sortGroupPair(pair);
  
  //the deepest text group
  GroupPtrs::const_iterator textGroup = pair.text.cbegin();
  //the deepest quads in the quad groups
  QuadIters deepestQuads = getDeepestQuadIters(pair.quad);
  Groups out;
  
  while (true) {
    QuadIterRef deepestQuad = getDeepestQuad(deepestQuads, pair.quad);
    
    //if there are no more quads then push the text if there is any and return
    if (!deepestQuad.valid) {
      while (textGroup != pair.text.cend()) {
        out.emplace_back(std::move(*(*textGroup)));
        textGroup++;
      }
      groups = std::move(out);
      return;
    } else {
      //if the deepestQuad is deeper than the text then push
      if (textGroup == pair.text.cend() || deepestQuad.iter->depth >= (*textGroup)->quads[0].depth) {
        if (out.size() == 0 || out.back().sameDepth) {
          out.push_back({{*deepestQuad.iter}, defaultMaterial, false});
        } else {
          out.back().quads.push_back(*deepestQuad.iter);
        }
        //we only increment the iterator if the quad is used
        deepestQuads[deepestQuad.groupIndex]++;
      //otherwise push the text
      } else {
        out.emplace_back(std::move(*(*textGroup)));
        textGroup++;
      }
    }
  }
}

void UI::Renderer::writeQuad(
  const UI::Renderer::Quad &quad,
  Ogre::uint32 i
) {
  PROFILE(UI::Renderer::writeQuad);

  //top left
  manualObject->position(quad.bounds.left, quad.bounds.top, quad.depth);
  manualObject->textureCoord(quad.textureCoords.left, quad.textureCoords.top);
  manualObject->colour(quad.color);
  //bottom left
  manualObject->position(quad.bounds.left, quad.bounds.bottom, quad.depth);
  manualObject->textureCoord(quad.textureCoords.left, quad.textureCoords.bottom);
  manualObject->colour(quad.color);
  //bottom right
  manualObject->position(quad.bounds.right, quad.bounds.bottom, quad.depth);
  manualObject->textureCoord(quad.textureCoords.right, quad.textureCoords.bottom);
  manualObject->colour(quad.color);
  //top right
  manualObject->position(quad.bounds.right, quad.bounds.top, quad.depth);
  manualObject->textureCoord(quad.textureCoords.right, quad.textureCoords.top);
  manualObject->colour(quad.color);
  
  manualObject->quad(i, i + 1, i + 2, i + 3);
}

void UI::Renderer::addSection(const Ogre::String &material) {
  PROFILE(UI::Renderer::addSection);

  manualObject->begin(material, Ogre::RenderOperation::OT_TRIANGLE_LIST);
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
}

void UI::Renderer::fillManualObject(const Groups &groups) {
  PROFILE(UI::Renderer::fillManualObject);

  if (groups.size() == 0) {
    return;
  }
  
  const size_t extraSection = groups[0].sameDepth;
  size_t numSections = manualObject->getNumSections();
  
  //if the materials mismatch, clear
  if (numSections > 1) {
    const Ogre::uint32 numSections32 = static_cast<Ogre::uint32>(numSections);
    for (Ogre::uint32 s = 1; s < numSections32; s += 2) {
      if (manualObject->getSection(s)->getMaterialName() != groups[s - extraSection].material) {
        manualObject->clear();
        numSections = 0;
        break;
      }
    }
  }
  
  //make sure there are enough sections
  while (numSections + extraSection < groups.size()) {
    if (numSections % 2) {
      addSection(groups[numSections - extraSection].material);
    } else {
      addSection(defaultMaterial);
    }
    numSections++;
  }
  
  size_t nextSection = 0;
  
  if (extraSection) {
    manualObject->beginUpdate(nextSection++);
    manualObject->end();
  }
  
  for (auto g = groups.cbegin(); g != groups.cend(); g++, nextSection++) {
    manualObject->beginUpdate(nextSection);
    Ogre::uint32 i = 0;
    for (auto q = g->quads.cbegin(); q != g->quads.cend(); q++, i += 4) {
      writeQuad(*q, i);
    }
    manualObject->end();
  }
}
