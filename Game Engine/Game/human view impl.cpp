//
//  human view impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "human view impl.hpp"

void Game::HumanViewImpl::init() {
  PROFILE(HumanViewImpl init);

  Game::HumanView::init();
  
  Platform::Window::Desc windowDesc;
  windowDesc.title = "Game Engine";
  windowDesc.size = {1280, 720};
  windowDesc.resizable = false;
  window = app->windowManager->openWindow(windowDesc);
  renderWindow = Platform::createRenderWindow(window, app->root.get());
  scene = app->root->createSceneManager(Ogre::ST_GENERIC);
    
  camera = scene->createCamera("Main Camera");
  camera->setPosition(0, 0, 80);
  camera->lookAt(0, 0, 0);
  camera->setNearClipDistance(5);
  
  viewport = renderWindow->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  camera->setAspectRatio(
    static_cast<Ogre::Real>(viewport->getActualWidth()) /
    viewport->getActualHeight()
  );
  camera->setAutoAspectRatio(true);
  
  uiRoot = std::make_unique<UI::Root>("test_ui", window, viewport, scene);
  
  Ogre::Entity *ogreEntity = scene->createEntity("ogrehead.mesh");
  ogrehead = scene->getRootSceneNode()->createChildSceneNode();
  ogrehead->attachObject(ogreEntity);
  
  scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
  
  Ogre::Light *light = scene->createLight("Main Light");
  Ogre::SceneNode *lightNode = scene->getRootSceneNode()->createChildSceneNode();
  lightNode->attachObject(light);
  lightNode->setPosition(20, 80, 50);
  
  UI::Button::Ptr button = std::make_shared<UI::Button>("main_button");
  {
    UI::AABB bounds;
    bounds.setBothOrigin(UI::Origin::CENTER);
    bounds.setSizeHeightRatio(0.25f, 2.0f);
    bounds.setSizeSpace(UI::Space::REL);
    bounds.setSizeAxis(UI::Axis::VERT);
    button->setBounds(bounds);
  }
  UI::Button::SetTextures buttonTextures("Out", "Hover", "Down");
  button->addStateChangeListener(buttonTextures);
  
  UI::Paragraph::Ptr paragraph = std::make_shared<UI::Paragraph>("paragraph");
  {
    UI::AABB bounds;
    bounds.setSpace(UI::Space::ABS);
    bounds.setSize({1.0f, 5.0f/12.0f});
    bounds.setBothOrigin(UI::Origin::BOTTOM);
    bounds.setSizeAxis(UI::Axis::BOTH);
    paragraph->setBounds(bounds);
  }
  paragraph->setFont("zapfino");
  paragraph->setText("How much wood could a woodchuck chuck if a woodchuck could chuck wood?");
  paragraph->setFontSize(32);
  paragraph->setAlign(UI::Paragraph::Align::LEFT);
  paragraph->setColor({1.0f, 1.0f, 1.0f, 1.0f});
  paragraph->setHeight(2);
  paragraph->setPassthrough(true);
  
  button->addChild(paragraph);
  
  UI::Button::Ptr otherButton = std::make_shared<UI::Button>("other_button");
  {
    UI::AABB bounds;
    bounds.setBothOrigin(UI::Origin::BOTTOM_RIGHT);
    bounds.setSize(0.5f);
    bounds.setSizeAxis(UI::Axis::BOTH);
    otherButton->setBounds(bounds);
  }
  auto onDown = [](UI::Button &) {
    std::cout << "Down\n";
  };
  auto onUp = [](UI::Button &) {
    std::cout << "Up\n";
  };
  auto onEnter = [](UI::Button &) {
    std::cout << "Enter\n";
  };
  auto onLeave = [](UI::Button &) {
    std::cout << "Leave\n";
  };
  otherButton->addStateChangeListener(buttonTextures);
  otherButton->addStateChangeListener(
    UI::Button::CallListeners(onDown, onUp, onEnter, onLeave)
  );
  
  button->addChild(otherButton);
  
  UI::Checkbox::Ptr checkbox = std::make_shared<UI::Checkbox>("checkbox");
  {
    UI::AABB bounds;
    bounds.setThisOrigin(UI::Origin::BOTTOM_RIGHT);
    bounds.setParentOrigin(UI::Origin::BOTTOM_LEFT);
    bounds.setSize(1.0f);
    bounds.setSizeAxis(UI::Axis::BOTH);
    checkbox->setBounds(bounds);
  }
  auto onCheck = [](UI::Checkbox &) {
    std::cout << "Checked\n";
  };
  auto onUnCheck = [](UI::Checkbox &) {
    std::cout << "Unchecked\n";
  };
  checkbox->addStateChangeListener(
    UI::Checkbox::SetTextures(
      "Unchecked", "Unchecked", "Unchecked",
      "Checked", "Checked", "Checked"
    )
  );
  checkbox->addStateChangeListener(
    UI::Checkbox::CallListeners(onUnCheck, onCheck)
  );
  
  button->addChild(checkbox);
  
  UI::Radio::Ptr radio0 = std::make_shared<UI::Radio>("radio_0", true);
  {
    UI::AABB bounds;
    bounds.setThisOrigin(UI::Origin::TOP_LEFT);
    bounds.setParentOrigin(UI::Origin::TOP_RIGHT);
    bounds.setSize(1.0f / 3.0f);
    bounds.setSizeAxis(UI::Axis::BOTH);
    radio0->setBounds(bounds);
  }
  UI::Radio::SetTextures radioTextures(
    "Unchecked", "Unchecked", "Unchecked",
    "Checked", "Checked", "Checked"
  );
  radio0->addStateChangeListener(radioTextures);
  UI::Radio::Ptr radio1 = std::make_shared<UI::Radio>("radio_1");
  {
    UI::AABB bounds;
    bounds.setThisOrigin(UI::Origin::TOP_LEFT);
    bounds.setParentOrigin(UI::Origin::TOP_RIGHT);
    bounds.setSize(1.0f / 3.0f);
    bounds.setSizeAxis(UI::Axis::BOTH);
    bounds.setPos({0.0f, 1.0f / 3.0f});
    radio1->setBounds(bounds);
  }
  radio1->addStateChangeListener(radioTextures);
  UI::Radio::Ptr radio2 = std::make_shared<UI::Radio>("radio_2");
  {
    UI::AABB bounds;
    bounds.setThisOrigin(UI::Origin::TOP_LEFT);
    bounds.setParentOrigin(UI::Origin::TOP_RIGHT);
    bounds.setSize(1.0f / 3.0f);
    bounds.setSizeAxis(UI::Axis::BOTH);
    bounds.setPos({0.0f, 2.0f / 3.0f});
    radio2->setBounds(bounds);
  }
  radio2->addStateChangeListener(radioTextures);
  
  button->addChild(radio0);
  button->addChild(radio1);
  button->addChild(radio2);
  
  /*UI::Image::Ptr image = std::make_shared<UI::Image>("overlay");
  {
    UI::AABB bounds;
    bounds.setSizeAxis(UI::Axis::BOTH);
    bounds.setSpace(UI::Space::ABS);
    image->setBounds(bounds);
  }
  image->setTexture("Overlay");
  image->setHeight(10);
  image->setPassthrough(true);
  button->addChild(image);*/
  
  UI::Button::Ptr triangle = std::make_shared<UI::Button>("triangle");
  {
    UI::AABB bounds;
    bounds.setThisOrigin(UI::Origin::TOP_LEFT);
    bounds.setParentOrigin(UI::Origin::TOP_RIGHT);
    bounds.setPos({1.0f / 3.0f, 0.0f});
    bounds.setSizeAxis(UI::Axis::VERT);
    triangle->setBounds(bounds);
  }
  triangle->setTexture("White triangle");
  triangle->setHitRegion({{0.5f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}});
  triangle->addStateChangeListener(
    []
    (UI::Button &button, UI::Button::State, UI::Button::State toState) {
      switch (toState) {
        case UI::Button::State::DOWN_OUT:
        case UI::Button::State::OUT:
          button.setColor({1.0f, 0.0f, 0.0f, 1.0f});
          break;
        case UI::Button::State::HOVER:
          button.setColor({0.0f, 1.0f, 0.0f, 1.0f});
          break;
        case UI::Button::State::DOWN:
          button.setColor({0.0f, 0.0f, 1.0f, 1.0f});
      }
    }
  );
  
  button->addChild(triangle);
  
  //the above mess is the reason why I planning on creating an XML based data
  //format for describing the UI. The callbacks will probably be written in
  //ChaiScript so that the whole thing is defined in data
  
  uiRoot->setChild(button);
}

void Game::HumanViewImpl::update(uint64_t delta) {
  PROFILE(HumanViewImpl update);
  
  ogrehead->yaw(Ogre::Radian(0.01f));
  HumanView::update(delta);
}

void Game::HumanViewImpl::quit() {
  PROFILE(HumanViewImpl quit);

  HumanView::quit();
}
