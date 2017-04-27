//
//  renderer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_renderer_hpp
#define engine_game_view_human_renderer_hpp

#include "../../Platform/Interface/window.hpp"
#include "element.hpp"
#include "aabb stack.hpp"
#include "height stack.hpp"
#include "../../Resource/Managers/texture atlas.hpp"
#include "caption.hpp"
#include "../../Utils/profiler.hpp"

namespace UI {
  class Renderer final : public Ogre::FrameListener {
  public:
    Renderer(const Ogre::String &,
             std::weak_ptr<Platform::Window>,
             Ogre::Viewport *,
             Ogre::SceneManager *);
    ~Renderer();
  
    void setRoot(Element::Ptr);
    void unSetRoot();
    
  private:
    static const size_t ESTIMATE_NUM_ELEMENTS;
    static const Height MAX_HEIGHT;
    
    ///A textured quad
    struct Quad {
      Quad(UI::SimpleAABB, Res::TextureAtlas::Sprite, UI::Color, UI::Height);
      
      Res::TextureAtlas::Sprite bounds;
      Res::TextureAtlas::Sprite textureCoords;
      Ogre::ColourValue color;
      Ogre::Real depth;
    };
    
    using Quads = std::vector<Quad>;
    using QuadIter = Quads::const_iterator;
    using QuadIters = std::vector<QuadIter>;
    struct QuadIterRef {
      QuadIter iter;
      //index of the quad group this iterator came from
      size_t groupIndex = 0;
      bool valid = false;
    };
    
    struct Group {
      Quads quads;
      std::string material;
      //all quads are the same depth
      //another way of saying that this is some text
      bool sameDepth;
    };
    
    using Groups = std::vector<Group>;
    using GroupPtrs = std::vector<Group *>;
    struct GroupPtrsPair {
      ///Pointers to groups that have sameDepth set to true
      GroupPtrs text;
      ///Pointers to groups that have sameDepth set to false
      GroupPtrs quad;
    };
  
    std::weak_ptr<Platform::Window> window;
    Ogre::Viewport *viewport;
    Element::Ptr root;
    Ogre::ManualObject *manualObject;
    Ogre::SceneNode *node;
    Res::TextureAtlasPtr atlas;
    std::string defaultMaterial;
    
    bool frameStarted(const Ogre::FrameEvent &) override;
    
    float getAspectRatio() const;
    
    void fillGroups(AABBStack &, const Element::Ptr, HeightStack &, Groups &);
    void fillQuads(
      const std::string &,
      const std::string &,
      SimpleAABB,
      Height,
      Color,
      Quads &
    );
    
    void sortQuads(Quads &);
    GroupPtrsPair partionGroups(Groups &);
    void sortGroupPair(GroupPtrsPair &);
    QuadIters getDeepestQuadIters(const GroupPtrs &);
    QuadIterRef getDeepestQuad(QuadIters &, const GroupPtrs &);
    void sortGroups(Groups &);
    
    void writeQuad(const UI::Renderer::Quad &, Ogre::uint32);
    void addSection(const Ogre::String &);
    void fillManualObject(const Groups &);
  };
}

#endif
