//
//  format.cpp
//  game engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "format.hpp"

const char *Math::Format::bin(uint64_t num) {
  static char out[65];
  out[64] = 0;
  uint8_t i = 64;
  do {
    out[--i] = (num & 1) + '0';
  } while (num >>= 1);
  return out + i;
}

const char *Math::Format::oct(uint64_t num) {
  static char out[23];
  out[22] = 0;
  uint8_t i = 22;
  do {
    out[--i] = (num & 7) + '0';
  } while (num >>= 3);
  return out + i;
}

const char *Math::Format::hex(uint64_t num) {
  static const char table[16] = {
    '0','1','2','3',
    '4','5','6','7',
    '8','9','A','B',
    'C','D','E','F'
  };
  
  static char out[17];
  out[16] = 0;
  uint8_t i = 16;
  do {
    out[--i] = table[num & 15];
  } while (num >>= 4);
  return out + i;
}

const char *Math::Format::binPad64(uint64_t num) {
  static char out[65] = {
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0', 0
  };
  uint8_t i = 64;
  while (num) {
    out[--i] = (num & 1) + '0';
    num >>= 1;
  }
  return out;
}

const char *Math::Format::octPad64(uint64_t num) {
  static char out[23] = {
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0',         0
  };
  uint8_t i = 22;
  while (num) {
    out[--i] = (num & 7) + '0';
    num >>= 3;
  }
  return out;
}

const char *Math::Format::hexPad64(uint64_t num) {
  static const char table[16] = {
    '0','1','2','3',
    '4','5','6','7',
    '8','9','A','B',
    'C','D','E','F'
  };

  static char out[17] = {
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0', 0
  };
  uint8_t i = 16;
  while (num) {
    out[--i] = table[num & 15];
    num >>= 4;
  }
  return out;
}

const char *Math::Format::binPad32(uint32_t num) {
  static char out[33] = {
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0', 0
  };
  uint8_t i = 32;
  while (num) {
    out[--i] = (num & 1) + '0';
    num >>= 1;
  }
  return out;
}

const char *Math::Format::octPad32(uint32_t num) {
  static char out[12] = {
    '0','0','0','0','0','0','0','0',
    '0','0','0',                     0
  };
  uint8_t i = 11;
  while (num) {
    out[--i] = (num & 7) + '0';
    num >>= 3;
  }
  return out;
}

const char *Math::Format::hexPad32(uint32_t num) {
  static const char table[16] = {
    '0','1','2','3',
    '4','5','6','7',
    '8','9','A','B',
    'C','D','E','F'
  };

  static char out[9] = {
    '0','0','0','0','0','0','0','0', 0
  };
  uint8_t i = 8;
  while (num) {
    out[--i] = table[(num & 15)];
    num >>= 4;
  }
  return out;
}

const char *Math::Format::binPad16(uint16_t num) {
  static char out[17] = {
    '0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','0', 0
  };
  uint8_t i = 16;
  while (num) {
    out[--i] = (num & 1) + '0';
    num >>= 1;
  }
  return out;
}

const char *Math::Format::octPad16(uint16_t num) {
  static char out[7] = {
    '0','0','0','0','0','0', 0
  };
  uint8_t i = 6;
  while (num) {
    out[--i] = (num & 7) + '0';
    num >>= 3;
  }
  return out;
}

const char *Math::Format::hexPad16(uint16_t num) {
  static const char table[16] = {
    '0','1','2','3',
    '4','5','6','7',
    '8','9','A','B',
    'C','D','E','F'
  };

  static char out[5] = {
    '0','0','0','0', 0
  };
  uint8_t i = 4;
  while (num) {
    out[--i] = table[(num & 15)];
    num >>= 4;
  }
  return out;
}

const char *Math::Format::binPad8(uint8_t num) {
  static char out[9] = {
    '0','0','0','0','0','0','0','0', 0
  };
  uint8_t i = 8;
  while (num) {
    out[--i] = (num & 1) + '0';
    num >>= 1;
  }
  return out;
}

const char *Math::Format::octPad8(uint8_t num) {
  static char out[4] = {
    '0','0','0', 0
  };
  uint8_t i = 3;
  while (num) {
    out[--i] = (num & 7) + '0';
    num >>= 3;
  }
  return out;
}

const char *Math::Format::hexPad8(uint8_t num) {
  static const char table[16] = {
    '0','1','2','3',
    '4','5','6','7',
    '8','9','A','B',
    'C','D','E','F'
  };

  static char out[3] = {
    '0','0', 0
  };
  uint8_t i = 2;
  while (num) {
    out[--i] = table[(num & 15)];
    num >>= 4;
  }
  return out;
}