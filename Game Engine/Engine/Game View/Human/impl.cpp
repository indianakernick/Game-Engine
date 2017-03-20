//
//  impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "impl.hpp"

void Game::HumanViewImpl::init() {
  PROFILE(HumanViewImpl init);

  Game::HumanView::init();
  
  Res::ID duck("Meshes/nightwing anim.dae");
  anim = new Graphics3D::Anim(duck);
  anim->play(0);
  anim->loop();
  
  glm::mat4 mat = glm::translate({}, glm::vec3(0.0f, -21.0f, 0.0f));
  mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  mat = glm::scale(mat, glm::vec3(1000.0f, 1000.0f, 1000.0f));
  Scene::Mesh::Ptr mesh = std::make_shared<Scene::Mesh>(73, mat, duck);
  
  camera = std::make_shared<Scene::Camera>(0xDEADBEEF, glm::mat4());
  Speed speed;
  speed.move = 25.0f;
  speed.vert = 25.0f;
  speed.look = 1.0f;
  controller = std::make_shared<CamControlFlyMouseless>(Bindings(),speed,glm::vec3(0.0f, 0.0f, 100.0f));
  
  mat = glm::translate({}, glm::vec3(0.0f, 30.0f, 25.0f));
  Scene::Light::CommonProps props;
  props.type = Scene::Light::SPHERE;
  props.color = {1.0f, 1.0f, 1.0f};
  props.intensity = 600.0f;
  Scene::Light::Ptr light = std::make_shared<Scene::Light>(42, mat, props);
  
  scene->addChild(mesh);
  scene->addChild(camera);
  scene->addChild(light);
  scene->setActiveCamera(0xDEADBEEF);
  
  UI::Button::Ptr button = std::make_shared<UI::Button>();
  {
    UI::AABB &buttonBounds = button->getBounds();
    buttonBounds.setOrigin(UI::Origin::CENTER);
    buttonBounds.setAspectRatio(2.0f);//400.0f / 200.0f
    buttonBounds.setHeight(0.25f);
    buttonBounds.setSizeSpace(UI::Space::REL);
    buttonBounds.setSizePropAxis(UI::Axis::VERT);
  }
  {
    UI::Button::Textures textures;
    textures.out = "Images/Out.png";
    textures.down = "Images/Down.png";
    textures.hover = "Images/Hover.png";
    button->setTextures(textures);
  }
  
  UI::Button::Ptr otherButton = std::make_shared<UI::Button>();
  {
    UI::AABB &buttonBounds = otherButton->getBounds();
    buttonBounds.setOrigin(UI::Origin::BOTTOM_RIGHT);
    buttonBounds.setSize({0.5f, 0.5f});
  }
  otherButton->setTextures(button->getTextures());
  button->addChild(otherButton);
  button->onDown([](UI::Button &) {
    std::cout << "Down\n";
  });
  button->onUp([](UI::Button &) {
    std::cout << "Up\n";
  });
  button->onEnter([](UI::Button &) {
    std::cout << "Enter\n";
  });
  button->onLeave([](UI::Button &) {
    std::cout << "Leave\n";
  });
  
  UI::Checkbox::Ptr checkbox = std::make_shared<UI::Checkbox>();
  {
    UI::AABB &bounds = checkbox->getBounds();
    bounds.setOrigin(UI::Origin::BOTTOM_RIGHT, UI::Origin::BOTTOM_LEFT);
    bounds.setSize({1.0f, 1.0f});
    bounds.setSizePropAxis(UI::Axis::BOTH);
  }
  {
    UI::Checkbox::Textures textures;
    textures.unCheckOut = "Images/Unchecked.png";
    textures.unCheckHover = textures.unCheckOut;
    textures.unCheckDown = textures.unCheckOut;
    
    textures.checkOut = "Images/Checked.png";
    textures.checkHover = textures.checkOut;
    textures.checkDown = textures.checkOut;
    checkbox->setTextures(textures);
  }
  checkbox->onCheck([](UI::Checkbox &) {
    std::cout << "Checked\n";
  });
  checkbox->onUncheck([](UI::Checkbox &) {
    std::cout << "Unchecked\n";
  });
  
  button->addChild(checkbox);
  
  //the above mess is the reason why I planning on creating an XML based data
  //format for describing the UI. The callbacks will probably be written in
  //ChaiScript so that the whole thing is defined in data
  
  ui->setChild(button);
}

void Game::HumanViewImpl::update(uint64_t delta) {
  PROFILE(HumanViewImpl update);

  HumanView::update(delta);
  anim->update(delta);
  controller->update(delta);
  camera->setToWorld(controller->getToWorld());
}

void Game::HumanViewImpl::quit() {
  PROFILE(HumanViewImpl quit);

  controller.reset();
  HumanView::quit();
  delete anim;
}
