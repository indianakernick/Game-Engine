//
//  safe down cast.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_safe_down_cast_hpp
#define engine_utils_safe_down_cast_hpp

#include <memory>
#include <cassert>

#ifdef RELEASE

namespace Utils {
  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    DERIVED *
  >
  safeDownCast(BASE * const base) {
    return static_cast<DERIVED * const>(base);
  }

  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    const DERIVED *
  >
  safeDownCast(const BASE * const base) {
    return static_cast<const DERIVED * const>(base);
  }

  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    std::shared_ptr<DERIVED>
  >
  safeDownCast(const std::shared_ptr<BASE> &base) {
    return std::static_pointer_cast<DERIVED>(base);
  }

  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    std::shared_ptr<const DERIVED>
  >
  safeDownCast(const std::shared_ptr<const BASE> &base) {
    return std::static_pointer_cast<const DERIVED>(base);
  }
}

#else

namespace Utils {
  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    DERIVED *
  >
  safeDownCast(BASE * const base) {
    DERIVED * const derived = dynamic_cast<DERIVED * const>(base);
    assert(derived);
    return derived;
  }

  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    const DERIVED *
  >
  safeDownCast(const BASE * const base) {
    const DERIVED * const derived = dynamic_cast<const DERIVED * const>(base);
    assert(derived);
    return derived;
  }

  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    std::shared_ptr<DERIVED>
  >
  safeDownCast(const std::shared_ptr<BASE> &base) {
    const std::shared_ptr<DERIVED> derived = std::dynamic_pointer_cast<DERIVED>(base);
    assert(derived);
    return derived;
  }

  ///Dynamic cast and assert that it was successful
  template <typename DERIVED, typename BASE>
  inline std::enable_if_t<
    std::is_base_of<BASE, DERIVED>::value &&
    !std::is_same<BASE, DERIVED>::value,
    std::shared_ptr<const DERIVED>
  >
  safeDownCast(const std::shared_ptr<const BASE> &base) {
    const std::shared_ptr<const DERIVED> derived = std::dynamic_pointer_cast<const DERIVED>(base);
    assert(derived);
    return derived;
  }
}

#endif

namespace Utils {
  ///Lock a std::weak_ptr and assert that it was successful
  template <typename T>
  inline std::shared_ptr<T> safeLock(const std::weak_ptr<T> &weak) {
    const std::shared_ptr<T> strong = weak.lock();
    assert(strong);
    return strong;
  }
}

#endif
