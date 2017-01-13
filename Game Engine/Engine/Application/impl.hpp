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
#include "opengl.hpp"
#include "Libraries/sdl.hpp"
#include "../Math/byteconstants.hpp"
#include "../Time/interval.hpp"
#include "../Resource/Loaders/all.hpp"
#include "../Time/stopwatch.hpp"

namespace Game {
  class AppImpl : public App {
  public:
    AppImpl();
  
    void init() override;
    void update(uint64_t) override;
    void quit() override;
    
    virtual std::string getCompany() override;
    virtual std::string getAppName() override;
  private:
    Time::IntervalSync<std::chrono::microseconds, Time::NO_WAIT> interval;
  };
}

#endif
