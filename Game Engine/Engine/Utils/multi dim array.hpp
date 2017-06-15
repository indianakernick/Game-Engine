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
  template <typename Coord, size_t DIMS>
  struct CoordsTraits {
    using Coords = std::array<Coord, DIMS>;
    using AccessIndex = size_t;
  };
  
  template <typename Coord>
  struct CoordsTraits<Coord, 1> {
    using Coords = Coord;
  };
  
  template <typename Coord>
  struct CoordsTraits<Coord, 2> {
    using Coords = glm::tvec2<Coord>;
    using AccessIndex = typename Coords::length_type;
  };
  
  template <typename Coord>
  struct CoordsTraits<Coord, 3> {
    using Coords = glm::tvec3<Coord>;
    using AccessIndex = typename Coords::length_type;
  };
  
  template <typename Coord>
  struct CoordsTraits<Coord, 4> {
    using Coords = glm::tvec4<Coord>;
    using AccessIndex = typename Coords::length_type;
  };
  
  enum class Order : uint8_t {
    ROW_MAJOR,
    COL_MAJOR
  };

  template <size_t DIMS, Order ORDER, typename CoordType, typename IndexType>
  class MultiDimArray;
  
  template <size_t DIMS, typename CoordType, typename IndexType>
  class MultiDimArray<DIMS, Order::ROW_MAJOR, CoordType, IndexType> {
  public:
    static_assert(DIMS != 0);
    static_assert(std::is_integral<CoordType>::value);
    static_assert(std::is_integral<IndexType>::value);
  
  private:
    using Traits = CoordsTraits<CoordType, DIMS>;
    using AccessIndex = typename Traits::AccessIndex;
    
  public:
    using Coords = typename Traits::Coords;
    static constexpr size_t DIMENSIONS = DIMS;
    static constexpr Order ORDER = Order::ROW_MAJOR;
    using Coord = CoordType;
    using Index = IndexType;
  
    MultiDimArray() = default;
    explicit MultiDimArray(const Coords newSize)
      : size(newSize) {}
    ~MultiDimArray() = default;
  
    void setSize(const Coords newSize) {
      size = newSize;
    }
    
    Coords getSize() const {
      return size;
    }
    
    Index posToIndex(const Coords pos) const {
      Index sum = 0;
      for (AccessIndex p = 0; p != DIMS; p++) {
        Index product = static_cast<Index>(pos[p]);
        for (AccessIndex s = p + 1; s != DIMS; s++) {
          product *= size[s];
        }
        sum += product;
      }
      return sum;
    }
    
    Coords indexToPos(const Index index) const {
      Coords pos;
      pos[AccessIndex(DIMS - 1)] = index % size[AccessIndex(DIMS - 1)];
      Coord product = 1;
      for (AccessIndex p = DIMS - 2; p != -AccessIndex(1); p--) {
        product *= size[p + 1];
        pos[p] = static_cast<Coord>(index / product);
      }
      return pos;
    }
    
  private:
    Coords size;
  };
  
  template <size_t DIMS, typename CoordType, typename IndexType>
  class MultiDimArray<DIMS, Order::COL_MAJOR, CoordType, IndexType> {
  public:
    static_assert(DIMS != 0);
    static_assert(std::is_integral<CoordType>::value);
    static_assert(std::is_integral<IndexType>::value);
    
  private:
    using Traits = CoordsTraits<CoordType, DIMS>;
    using AccessIndex = typename Traits::AccessIndex;
  
  public:
    using Coords = typename Traits::Coords;
    static constexpr size_t DIMENSIONS = DIMS;
    static constexpr Order ORDER = Order::COL_MAJOR;
    using Coord = CoordType;
    using Index = IndexType;
  
    MultiDimArray() = default;
    explicit MultiDimArray(const Coords newSize)
      : size(newSize) {}
    ~MultiDimArray() = default;
  
    void setSize(const Coords newSize) {
      size = newSize;
    }
    
    Coords getSize() const {
      return size;
    }
    
    Index posToIndex(const Coords pos) const {
      Index sum = 0;
      for (AccessIndex p = 0; p != DIMS; p++) {
        Index product = static_cast<Index>(pos[p]);
        for (AccessIndex s = 0; s != p; s++) {
          product *= size[s];
        }
        sum += product;
      }
      return sum;
    }
    
    Coords indexToPos(const Index index) const {
      Coords pos;
      pos[AccessIndex(0)] = index % size[AccessIndex(0)];
      Coord product = 1;
      for (AccessIndex p = 1; p != DIMS; p++) {
        product *= size[p - 1];
        pos[p] = static_cast<Coord>(index / product);
      }
      return pos;
    }
    
  private:
    Coords size;
  };
  
  template <Order MEM_ORDER, typename CoordType, typename IndexType>
  class MultiDimArray<1, MEM_ORDER, CoordType, IndexType> {
  public:
    static_assert(std::is_integral<CoordType>::value);
    static_assert(std::is_integral<IndexType>::value);
    
  private:
    using Traits = CoordsTraits<CoordType, 1>;
  
  public:
    using Coords = typename Traits::Coords;
    static constexpr size_t DIMENSIONS = 1;
    static constexpr Order ORDER = MEM_ORDER;
    using Coord = CoordType;
    using Index = IndexType;
    
    MultiDimArray() = default;
    ~MultiDimArray() = default;
    
    void setSize(const Coord newSize) {
      size = newSize;
    }
    
    Coord getSize() const {
      return size;
    }
    
    Index posToIndex(const Coord pos) const {
      return static_cast<Index>(pos);
    }
    
    Coord indexToPos(const Index index) const {
      return static_cast<Coord>(index);
    }
  
  private:
    Coord size;
  };
}

#endif
