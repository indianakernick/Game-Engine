//
//  impl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_application_impl_hpp
#define engine_application_impl_hpp

#include "base.hpp"
#include "../Game View/Human/impl.hpp"
#include "../Game Logic/impl.hpp"

namespace Game {
  class AppImpl final : public App {
  public:
    AppImpl();
    virtual ~AppImpl() = default;
  
  private:
    void init() override;
    void update(uint64_t) override;
    void quit() override;
    
    std::string getCompany() const override;
    std::string getAppName() const override;
    std::string getPluginFile() const override;
    std::string getConfigFile() const override;
    std::string getResourceFile() const override;
  };
}

#endif
