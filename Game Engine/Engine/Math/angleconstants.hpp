//
//  angleconstants.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef angleconstants_hpp
#define angleconstants_hpp

#include "constants.hpp"
#include <math.h>

//i'll only ever use degRad and radDeg!

namespace Math {
  ///Max value for Rotations (Turns)
  constexpr double MAX_ROT = 1;
  ///Max value for Radians
  constexpr double MAX_RAD = PIt2;
  ///Max value for Degrees
  constexpr double MAX_DEG = 360;
  ///Max value for Gon (Gradians)
  constexpr double MAX_GON = 400;
  
  ///Rotations (Turns) to Radians
  constexpr double ROT_RAD = MAX_RAD;
  ///Rotations (Turns) to Degrees
  constexpr double ROT_DEG = MAX_DEG;
  ///Rotations (Turns) to Gon (Gradians)
  constexpr double ROT_GON = MAX_GON;
  
  ///Radians to Rotations (Turns)
  constexpr double RAD_ROT = 0.1591549430918953;//1 / PIt2
  ///Radians to Degrees
  constexpr double RAD_DEG = 57.295779513082320;//360 / PI
  ///Radians to Gon (Gradians)
  constexpr double RAD_GON = 63.661977236758134;//200 / PI
  
  ///Degrees to Rotations (Turns)
  constexpr double DEG_ROT = 0.0027777777777777;//1 / 360
  ///Degrees to Radians
  constexpr double DEG_RAD = 0.0174532925199432;//PI / 180
  ///Degrees to Gon (Gradians)
  constexpr double DEG_GON = 1.1111111111111111;//400 / 360
  
  ///Gon (Gradians) to Rotations (Turns)
  constexpr double GON_ROT = 0.0025;//1 / 400
  ///Gon (Gradians) to Radians
  constexpr double GON_RAD = 0.0157079632679489;//PI / 200
  ///Gon (Gradians) to Degrees
  constexpr double GON_DEG = 0.9;//360 / 400
  
  ///Normalize Degrees
  inline double normDeg(double deg) {
    return fmod(deg, MAX_DEG);
  }
  ///Normalize Radians
  inline double normRad(double rad) {
    return fmod(rad, MAX_RAD);
  }
  ///Normalize Rotations (Turns)
  inline double normRot(double rot) {
    return fmod(rot, MAX_ROT);
  }
  ///Normalize Gon (Gradians)
  inline double normGon(double gon) {
    return fmod(gon, MAX_GON);
  }
};

constexpr double operator""_rot(long double value) {
  return value * Math::ROT_RAD;
}
constexpr double operator""_rad(long double value) {
  return value;
}
constexpr double operator""_deg(long double value) {
  return value * Math::DEG_RAD;
}
constexpr double operator""_gon(long double value) {
  return value * Math::GON_RAD;
}

#endif
