//
//  line col.hpp
//  Game Engine
//
//  Created by Indi Kernick on 25/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_line_col_hpp
#define engine_resource_loaders_line_col_hpp

#include <cctype>
#include <cstdio>
#include <cassert>

namespace Res {
  ///Keeps track of lines and columns in text.
  ///Great for writing error messages in parsers
  class LineCol {
  public:
    using LineType = unsigned int;
    using ColType = unsigned int;
    static const ColType SIZE_OF_TAB = 8;
    static const LineType FIRST_LINE = 1;
    static const ColType FIRST_COL = 1;
  
    explicit LineCol(LineType line = FIRST_LINE,
                     ColType  col  = FIRST_COL);
    
    ///Move line and col according to the char.
    ///Call this at the end of the loop with the char you just processed
    void update(char);
    ///This calls update(char) for each char in the null terminated string
    void update(const char *);
    ///This calls update(char) for the first n chars in the string
    void update(const char *, size_t);
    ///Sets line to FIRST_LINE and col to FIRST_COL
    void reset();
    
    LineType getLine() const;
    ColType getCol() const;
    const char *getStr() const;
  private:
    LineType line;
    ColType col;
  };
}

#endif
