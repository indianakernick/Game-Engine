//
//  combine functions.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_combine_functions_hpp
#define engine_utils_combine_functions_hpp

#include <tuple>
#include <utility>

template<typename Tuple, size_t... Is, typename... Args>
void callFuncs(Tuple &&tuple, std::index_sequence<Is...>, Args &&... args) {
  //not forwarding the arguments
  (std::get<Is>(tuple)(args...), ...);
}

template<typename... Funcs>
auto concat(Funcs &&... funcs) {
  return [
    funcs = std::make_tuple(std::forward<Funcs>(funcs)...)
  ] (auto&&...args) mutable {
    callFuncs(
      funcs,
      std::make_index_sequence<sizeof...(Funcs)>(),
      std::forward<decltype(args)>(args)...
    );
  };
};

#endif
