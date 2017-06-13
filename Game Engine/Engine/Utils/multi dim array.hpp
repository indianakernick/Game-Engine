//
//  multi dim array.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_multi_dim_array_hpp
#define engine_utils_multi_dim_array_hpp

#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//The formulas are from wikipedia
//https://en.wikipedia.org/wiki/Row-_and_column-major_order

//GCC 7.1 and Clang 4.0 unroll the loops and inline the call to access

//MultiDimArray is just as efficient as manually writing out
//the dimension specific formula

namespace Utils {
  template <typename Coord, size_t DIMENSIONS>
  struct CoordsTraits {
    using type = std::array<Coord, DIMENSIONS>;
    
    static Coord &access(type &coords, const size_t i) {
      return coords[i];
    }
    
    static const Coord &access(const type &coords, const size_t i) {
      return coords[i];
    }
  };
  
  template <typename Coord>
  struct CoordsTraits<Coord, 2> {
    using type = glm::tvec2<Coord>;
    
    static Coord &access(type &coords, const size_t i) {
      return (&coords.x)[i];
    }
    
    static const Coord &access(const type &coords, const size_t i) {
      return (&coords.x)[i];
    }
  };
  
  template <typename Coord>
  struct CoordsTraits<Coord, 3> {
    using type = glm::tvec3<Coord>;
    
    static Coord &access(type &coords, const size_t i) {
      return (&coords.x)[i];
    }
    
    static const Coord &access(const type &coords, const size_t i) {
      return (&coords.x)[i];
    }
  };
  
  template <typename Coord>
  struct CoordsTraits<Coord, 4> {
    using type = glm::tvec4<Coord>;
    
    static Coord &access(type &coords, const size_t i) {
      return (&coords.x)[i];
    }
    
    static const Coord &access(const type &coords, const size_t i) {
      return (&coords.x)[i];
    }
  };
  
  enum class Order : uint8_t {
    ROW_MAJOR,
    COL_MAJOR
  };

  template <size_t DIMENSIONS, Order ORDER, typename Coord, typename Index>
  class MultiDimArray;
  
  template <size_t DIMENSIONS, typename Coord, typename Index>
  class MultiDimArray<DIMENSIONS, Order::ROW_MAJOR, Coord, Index> {
  public:
    static_assert(DIMENSIONS != 0);
    static_assert(std::is_integral<Coord>::value);
    static_assert(std::is_integral<Index>::value);
  
  private:
    using Traits = CoordsTraits<Coord, DIMENSIONS>;
    
  public:
    using Coords = typename Traits::type;
  
    MultiDimArray() = default;
    explicit MultiDimArray(const Coords newSize) {
      setSize(newSize);
    }
    ~MultiDimArray() = default;
  
    void setSize(const Coords newSize) {
      for (size_t s = 0; s != DIMENSIONS; s++) {
        size[s] = Traits::access(newSize, s + 1);
      }
    }
    
    Index posToIndex(const Coords pos) const {
      Index sum = 0;
      for (size_t p = 0; p != DIMENSIONS; p++) {
        Index product = static_cast<Index>(Traits::access(pos, p));
        for (size_t s = p; s != DIMENSIONS - 1; s++) {
          product *= size[s];
        }
        sum += product;
      }
      return sum;
    }
    
    Coords indexToPos(const Index index) const {
      Coords pos;
      pos[DIMENSIONS - 1] = index % size[DIMENSIONS - 2];
      Coord product = 1;
      for (size_t p = DIMENSIONS - 2; p != -size_t(1); p--) {
        product *= size[p];
        Traits::access(pos, p) = static_cast<Coord>(index / product);
      }
      return pos;
    }
    
  private:
    std::array<Coord, DIMENSIONS - 1> size;
  };
  
  template <size_t DIMENSIONS, typename Coord, typename Index>
  class MultiDimArray<DIMENSIONS, Order::COL_MAJOR, Coord, Index> {
  public:
    static_assert(DIMENSIONS != 0);
    static_assert(std::is_integral<Coord>::value);
    static_assert(std::is_integral<Index>::value);
    
  private:
    using Traits = CoordsTraits<Coord, DIMENSIONS>;
  
  public:
    using Coords = typename Traits::type;
  
    MultiDimArray() = default;
    explicit MultiDimArray(const Coords newSize) {
      setSize(newSize);
    }
    ~MultiDimArray() = default;
  
    void setSize(const Coords newSize) {
      for (size_t s = 0; s != DIMENSIONS; s++) {
        size[s] = Traits::access(newSize, s);
      }
    }
    
    Index posToIndex(const Coords pos) const {
      Index sum = 0;
      for (size_t p = 0; p != DIMENSIONS; p++) {
        Index product = static_cast<Index>(Traits::access(pos, p));
        for (size_t s = 0; s != p; s++) {
          product *= size[s];
        }
        sum += product;
      }
      return sum;
    }
    
    Coords indexToPos(const Index index) const {
      Coords pos;
      pos[0] = index % size[0];
      Coord product = 1;
      for (size_t p = 1; p != DIMENSIONS; p++) {
        product *= size[p - 1];
        Traits::access(pos, p) = static_cast<Coord>(index / product);
      }
      return pos;
    }
    
  private:
    std::array<Coord, DIMENSIONS - 1> size;
  };
  
  template <Order ORDER, typename Coord, typename Index>
  class MultiDimArray<1, ORDER, Coord, Index> {
  public:
    static_assert(std::is_integral<Coord>::value);
    static_assert(std::is_integral<Index>::value);
    
    MultiDimArray() = default;
    ~MultiDimArray() = default;
    
    Index posToIndex(const Coord pos) const {
      return static_cast<Index>(pos);
    }
    
    Coord indexToPos(const Index index) const {
      return static_cast<Coord>(index);
    }
  };
}

#endif
