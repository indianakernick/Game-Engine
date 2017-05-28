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
#include "paragraph.hpp"
#include "../../Utils/profiler.hpp"
#include <experimental/string_view>
#include "conversions.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

namespace UI {
  class Renderer final : public Ogre::FrameListener {
  public:
    Renderer(
      std::weak_ptr<Platform::Window>,
      Ogre::Viewport *,
      Ogre::SceneManager *
    );
    ~Renderer();
  
    void setRoot(Element::Ptr, const std::string &, const std::string &);
    void unSetRoot();
    
  private:
    static const size_t ESTIMATE_NUM_ELEMENTS;
    static const Ogre::Real MAX_HEIGHT;
    static const Ogre::Real MAX_TEXTURES;
    
    ///A textured quad
    struct Quad {
      Quad(Bounds, TexCoords, Color, Height, const Trans2D &);
      
      TexCoords texCoords;
      Ogre::ColourValue color;
      Ogre::Real depth;
      Trans2D transform;
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
    Res::TextureAtlas::Ptr atlas;
    std::string defaultMaterial;
    
    bool frameStarted(const Ogre::FrameEvent &) override;
    
    Coord getWindowAspectRatio() const;
    PointPx getWindowSize() const;
    
    void fillGroups(AABBStack &, const Element::Ptr, HeightStack &, Groups &);
    
    bool cropQuadBounds(BoundsPx, PointPx, BoundsPx &, TexCoords &);
    Res::TextureAtlas::Ptr getAtlas(const std::string &);
    const Res::TextureAtlas::FontFace &getFontFace(const std::string &, FontSize);
    const Res::TextureAtlas::FontFace &getFontFace(const Res::TextureAtlas::Ptr, FontSize);
    
    struct TextInfo {
      std::experimental::string_view text;
      Color color;
      Height height;
      PointPx pos;
    };
    
    void renderText(const Res::TextureAtlas::FontFace &, PointPx, const TextInfo &, BoundsPx, Quads &);
    void renderParagraph(const Paragraph::Ptr, Bounds, Height, Quads &);
    
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
