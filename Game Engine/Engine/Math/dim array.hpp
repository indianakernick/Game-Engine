//
//  dim array.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_dim_array_hpp
#define engine_math_dim_array_hpp

#include <array>

namespace Math {
  enum class Order : uint8_t {
    ROW_MAJOR,
    COL_MAJOR
  };

  template <size_t DIMENSIONS, Order ORDER, typename Coord, typename Index>
  class DimArray;
  
  template <size_t DIMENSIONS, typename Coord, typename Index>
  class DimArray<DIMENSIONS, Order::ROW_MAJOR, Coord, Index> {
  public:
    static_assert(DIMENSIONS != 0);
    static_assert(std::is_integral<Coord>::value);
    static_assert(std::is_integral<Index>::value);
  
    using Coords = std::array<Coord, DIMENSIONS>;
  
    DimArray() = default;
    explicit DimArray(const Coords newSize) {
      for (size_t i = 0; i != size.size(); i++) {
        size[i] = newSize[i + 1];
      }
    }
    ~DimArray() = default;
  
    void setSize(const Coords newSize) {
      for (size_t i = 0; i != size.size(); i++) {
        size[i] = newSize[i + 1];
      }
    }
    
    Index posToIndex(const Coords pos) const {
      Index sum = 0;
      for (size_t k = 0; k != DIMENSIONS; k++) {
        Index product = pos[k];
        for (size_t l = k; l != DIMENSIONS - 1; l++) {
          product *= size[l];
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
        pos[p] = index / product;
      }
      return pos;
    }
    
  private:
    std::array<Coord, DIMENSIONS - 1> size;
  };
  
  template <size_t DIMENSIONS, typename Coord, typename Index>
  class DimArray<DIMENSIONS, Order::COL_MAJOR, Coord, Index> {
  public:
    static_assert(DIMENSIONS != 0);
    static_assert(std::is_integral<Coord>::value);
    static_assert(std::is_integral<Index>::value);
    
    using Coords = std::array<Coord, DIMENSIONS>;
  
    DimArray() = default;
    explicit DimArray(const Coords newSize) {
      for (size_t i = 0; i != size.size(); i++) {
        size[i] = newSize[i];
      }
    }
    ~DimArray() = default;
  
    void setSize(const Coords newSize) {
      for (size_t i = 0; i != size.size(); i++) {
        size[i] = newSize[i];
      }
    }
    
    Index posToIndex(const Coords pos) const {
      Index sum = 0;
      for (size_t p = 0; p != DIMENSIONS; p++) {
        Index product = pos[p];
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
        pos[p] = index / product;
      }
      return pos;
    }
    
  private:
    std::array<Coord, DIMENSIONS - 1> size;
  };
  
  template <Order ORDER, typename Coord, typename Index>
  class DimArray<1, ORDER, Coord, Index> {
  public:
    static_assert(std::is_integral<Coord>::value);
    static_assert(std::is_integral<Index>::value);
    
    DimArray() = default;
    ~DimArray() = default;
    
    Index posToIndex(const Coord pos) const {
      return static_cast<Index>(pos);
    }
    
    Coord indexToPos(const Index index) const {
      return static_cast<Coord>(index);
    }
  };
}

#endif
