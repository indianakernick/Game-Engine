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
    
    struct DrawObject {
      DrawObject(UI::SimpleAABB, Res::TextureAtlas::Sprite, glm::vec4, UI::Height);
    
      Res::TextureAtlas::Sprite bounds;
      Res::TextureAtlas::Sprite textureCoords;
      Ogre::ColourValue color;
      Ogre::Real depth;
    };
    
    using DrawObjects = std::vector<DrawObject>;
  
    std::weak_ptr<Platform::Window> window;
    Ogre::Viewport *viewport;
    Element::Ptr root;
    Ogre::ManualObject *manualObject;
    Ogre::SceneNode *node;
    Res::TextureAtlasPtr atlas;
    
    bool frameStarted(const Ogre::FrameEvent &) override;
    
    float getAspectRatio() const;
    
    void fillDrawObjects(
      UI::AABBStack &,
      const Res::TextureAtlasPtr &,
      const UI::Element::Ptr,
      UI::HeightStack &,
      DrawObjects &
    );
    void fillManualObject(const DrawObjects &);
  };
}

#endif
