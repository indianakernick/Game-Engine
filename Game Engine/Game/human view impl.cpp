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
  
  Ogre::Entity *ogreEntity = scene->createEntity("ogrehead.mesh");
  ogrehead = scene->getRootSceneNode()->createChildSceneNode();
  ogrehead->attachObject(ogreEntity);
  
  scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
  
  Ogre::Light *light = scene->createLight("Main Light");
  Ogre::SceneNode *lightNode = scene->getRootSceneNode()->createChildSceneNode();
  lightNode->attachObject(light);
  lightNode->setPosition(20, 80, 50);
  
  Res::UIScreen::Ptr uiScreen = Res::UIScreenManager::getSingleton().load(
    "test_ui.xml",
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::UIScreen>();
  uiRoot = std::make_unique<UI::Root>("test_ui", window, viewport, scene);
  uiRoot->setChild(uiScreen->getRoot());
  
  UI::Button::Ptr button = safeDownCast<UI::Button>(uiRoot->getChild());
  UI::Button::SetTextures buttonTextures("Out", "Hover", "Down");
  button->addStateChangeListener(buttonTextures);
  
  UI::Button::Ptr otherButton = button->getChild<UI::Button>("other_button");
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
  
  UI::Checkbox::Ptr checkbox = button->getChild<UI::Checkbox>("checkbox");
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
  
  UI::Radio::Ptr radio0 = button->getChild<UI::Radio>("radio_0");
  UI::Radio::SetTextures radioTextures(
    "Unchecked", "Unchecked", "Unchecked",
    "Checked", "Checked", "Checked"
  );
  radio0->addStateChangeListener(radioTextures);
  UI::Radio::Ptr radio1 = button->getChild<UI::Radio>("radio_1");
  radio1->addStateChangeListener(radioTextures);
  UI::Radio::Ptr radio2 = button->getChild<UI::Radio>("radio_2");
  radio2->addStateChangeListener(radioTextures);
  
  UI::Button::Ptr triangle = button->getChild<UI::Button>("triangle");
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
