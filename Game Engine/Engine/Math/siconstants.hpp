//
//  siconstants.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef siconstants_hpp
#define siconstants_hpp

namespace Math {
  namespace SI {
    constexpr double YOTTA = 1e+24; // septillion
    constexpr double ZETTA = 1e+21; // sextillion
    constexpr double EXA   = 1e+18; // quintillion
    constexpr double PETA  = 1e+15; // quadrillion
    constexpr double TERA  = 1e+12; // trillion
    constexpr double GIGA  = 1e+09; // billion
    constexpr double MEGA  = 1e+06; // million
    constexpr double KILO  = 1e+03; // thousand
    constexpr double HECTO = 1e+02; // hundred
    constexpr double DECA  = 1e+01; // ten
    constexpr double ONE   = 1e+00; // one
    constexpr double DECI  = 1e-01; // tenth
    constexpr double CENTI = 1e-02; // hundredth
    constexpr double MILLI = 1e-03; // thousandth
    constexpr double MICRO = 1e-06; // millionth
    constexpr double NANO  = 1e-09; // billionth
    constexpr double PICO  = 1e-12; // trillionth
    constexpr double FEMTO = 1e-15; // quadrillionth
    constexpr double ATTO  = 1e-18; // quintillionth
    constexpr double ZEPTO = 1e-21; // sextillionth
    constexpr double YOCTO = 1e-24; // septillionth

    /*
    std::string names[21] = {"YOTTA","ZETTA","EXA","PETA","TERA","GIGA","MEGA","KILO","HECTO","DECA","ONE","DECI","CENTI","MILLI","MICRO","NANO","PICO","FEMTO","ATTO","ZEPTO","YOCTO"};
    int values[21] = {24,21,18,15,12,9,6,3,2,1,+0,-1,-2,-3,-6,-9,-12,-15,-18,-21,-24};
    
    for (int i = 0; i < 21; i++) {
      for (int j = 0; j < 21; j++) {
        if (i == j) {
          continue;
        }
        std::string newName = names[i] + "_" + names[j];
        std::cout << "    constexpr double ";
        std::cout.width(11);
        std::cout << std::left << newName;
        int value = values[i] - values[j];
        std::string valueStr = std::to_string(value);
        if (value < 0) {
          valueStr.erase(valueStr.begin());
          if (valueStr.size() == 1) {
            valueStr = "0" + valueStr;
          }
          valueStr = "-" + valueStr;
        } else {
          if (valueStr.size() == 1) {
            valueStr = "0" + valueStr;
          }
          valueStr = "+" + valueStr;
        }
        valueStr = "1e" + valueStr;
        std::cout << " = " << valueStr << ";\n";
      }
    }
    */
    
    constexpr double YOTTA_ZETTA = 1e+03;
    constexpr double YOTTA_EXA   = 1e+06;
    constexpr double YOTTA_PETA  = 1e+09;
    constexpr double YOTTA_TERA  = 1e+12;
    constexpr double YOTTA_GIGA  = 1e+15;
    constexpr double YOTTA_MEGA  = 1e+18;
    constexpr double YOTTA_KILO  = 1e+21;
    constexpr double YOTTA_HECTO = 1e+22;
    constexpr double YOTTA_DECA  = 1e+23;
    constexpr double YOTTA_ONE   = 1e+24;
    constexpr double YOTTA_DECI  = 1e+25;
    constexpr double YOTTA_CENTI = 1e+26;
    constexpr double YOTTA_MILLI = 1e+27;
    constexpr double YOTTA_MICRO = 1e+30;
    constexpr double YOTTA_NANO  = 1e+33;
    constexpr double YOTTA_PICO  = 1e+36;
    constexpr double YOTTA_FEMTO = 1e+39;
    constexpr double YOTTA_ATTO  = 1e+42;
    constexpr double YOTTA_ZEPTO = 1e+45;
    constexpr double YOTTA_YOCTO = 1e+48;
    constexpr double ZETTA_YOTTA = 1e-03;
    constexpr double ZETTA_EXA   = 1e+03;
    constexpr double ZETTA_PETA  = 1e+06;
    constexpr double ZETTA_TERA  = 1e+09;
    constexpr double ZETTA_GIGA  = 1e+12;
    constexpr double ZETTA_MEGA  = 1e+15;
    constexpr double ZETTA_KILO  = 1e+18;
    constexpr double ZETTA_HECTO = 1e+19;
    constexpr double ZETTA_DECA  = 1e+20;
    constexpr double ZETTA_ONE   = 1e+21;
    constexpr double ZETTA_DECI  = 1e+22;
    constexpr double ZETTA_CENTI = 1e+23;
    constexpr double ZETTA_MILLI = 1e+24;
    constexpr double ZETTA_MICRO = 1e+27;
    constexpr double ZETTA_NANO  = 1e+30;
    constexpr double ZETTA_PICO  = 1e+33;
    constexpr double ZETTA_FEMTO = 1e+36;
    constexpr double ZETTA_ATTO  = 1e+39;
    constexpr double ZETTA_ZEPTO = 1e+42;
    constexpr double ZETTA_YOCTO = 1e+45;
    constexpr double EXA_YOTTA   = 1e-06;
    constexpr double EXA_ZETTA   = 1e-03;
    constexpr double EXA_PETA    = 1e+03;
    constexpr double EXA_TERA    = 1e+06;
    constexpr double EXA_GIGA    = 1e+09;
    constexpr double EXA_MEGA    = 1e+12;
    constexpr double EXA_KILO    = 1e+15;
    constexpr double EXA_HECTO   = 1e+16;
    constexpr double EXA_DECA    = 1e+17;
    constexpr double EXA_ONE     = 1e+18;
    constexpr double EXA_DECI    = 1e+19;
    constexpr double EXA_CENTI   = 1e+20;
    constexpr double EXA_MILLI   = 1e+21;
    constexpr double EXA_MICRO   = 1e+24;
    constexpr double EXA_NANO    = 1e+27;
    constexpr double EXA_PICO    = 1e+30;
    constexpr double EXA_FEMTO   = 1e+33;
    constexpr double EXA_ATTO    = 1e+36;
    constexpr double EXA_ZEPTO   = 1e+39;
    constexpr double EXA_YOCTO   = 1e+42;
    constexpr double PETA_YOTTA  = 1e-09;
    constexpr double PETA_ZETTA  = 1e-06;
    constexpr double PETA_EXA    = 1e-03;
    constexpr double PETA_TERA   = 1e+03;
    constexpr double PETA_GIGA   = 1e+06;
    constexpr double PETA_MEGA   = 1e+09;
    constexpr double PETA_KILO   = 1e+12;
    constexpr double PETA_HECTO  = 1e+13;
    constexpr double PETA_DECA   = 1e+14;
    constexpr double PETA_ONE    = 1e+15;
    constexpr double PETA_DECI   = 1e+16;
    constexpr double PETA_CENTI  = 1e+17;
    constexpr double PETA_MILLI  = 1e+18;
    constexpr double PETA_MICRO  = 1e+21;
    constexpr double PETA_NANO   = 1e+24;
    constexpr double PETA_PICO   = 1e+27;
    constexpr double PETA_FEMTO  = 1e+30;
    constexpr double PETA_ATTO   = 1e+33;
    constexpr double PETA_ZEPTO  = 1e+36;
    constexpr double PETA_YOCTO  = 1e+39;
    constexpr double TERA_YOTTA  = 1e-12;
    constexpr double TERA_ZETTA  = 1e-09;
    constexpr double TERA_EXA    = 1e-06;
    constexpr double TERA_PETA   = 1e-03;
    constexpr double TERA_GIGA   = 1e+03;
    constexpr double TERA_MEGA   = 1e+06;
    constexpr double TERA_KILO   = 1e+09;
    constexpr double TERA_HECTO  = 1e+10;
    constexpr double TERA_DECA   = 1e+11;
    constexpr double TERA_ONE    = 1e+12;
    constexpr double TERA_DECI   = 1e+13;
    constexpr double TERA_CENTI  = 1e+14;
    constexpr double TERA_MILLI  = 1e+15;
    constexpr double TERA_MICRO  = 1e+18;
    constexpr double TERA_NANO   = 1e+21;
    constexpr double TERA_PICO   = 1e+24;
    constexpr double TERA_FEMTO  = 1e+27;
    constexpr double TERA_ATTO   = 1e+30;
    constexpr double TERA_ZEPTO  = 1e+33;
    constexpr double TERA_YOCTO  = 1e+36;
    constexpr double GIGA_YOTTA  = 1e-15;
    constexpr double GIGA_ZETTA  = 1e-12;
    constexpr double GIGA_EXA    = 1e-09;
    constexpr double GIGA_PETA   = 1e-06;
    constexpr double GIGA_TERA   = 1e-03;
    constexpr double GIGA_MEGA   = 1e+03;
    constexpr double GIGA_KILO   = 1e+06;
    constexpr double GIGA_HECTO  = 1e+07;
    constexpr double GIGA_DECA   = 1e+08;
    constexpr double GIGA_ONE    = 1e+09;
    constexpr double GIGA_DECI   = 1e+10;
    constexpr double GIGA_CENTI  = 1e+11;
    constexpr double GIGA_MILLI  = 1e+12;
    constexpr double GIGA_MICRO  = 1e+15;
    constexpr double GIGA_NANO   = 1e+18;
    constexpr double GIGA_PICO   = 1e+21;
    constexpr double GIGA_FEMTO  = 1e+24;
    constexpr double GIGA_ATTO   = 1e+27;
    constexpr double GIGA_ZEPTO  = 1e+30;
    constexpr double GIGA_YOCTO  = 1e+33;
    constexpr double MEGA_YOTTA  = 1e-18;
    constexpr double MEGA_ZETTA  = 1e-15;
    constexpr double MEGA_EXA    = 1e-12;
    constexpr double MEGA_PETA   = 1e-09;
    constexpr double MEGA_TERA   = 1e-06;
    constexpr double MEGA_GIGA   = 1e-03;
    constexpr double MEGA_KILO   = 1e+03;
    constexpr double MEGA_HECTO  = 1e+04;
    constexpr double MEGA_DECA   = 1e+05;
    constexpr double MEGA_ONE    = 1e+06;
    constexpr double MEGA_DECI   = 1e+07;
    constexpr double MEGA_CENTI  = 1e+08;
    constexpr double MEGA_MILLI  = 1e+09;
    constexpr double MEGA_MICRO  = 1e+12;
    constexpr double MEGA_NANO   = 1e+15;
    constexpr double MEGA_PICO   = 1e+18;
    constexpr double MEGA_FEMTO  = 1e+21;
    constexpr double MEGA_ATTO   = 1e+24;
    constexpr double MEGA_ZEPTO  = 1e+27;
    constexpr double MEGA_YOCTO  = 1e+30;
    constexpr double KILO_YOTTA  = 1e-21;
    constexpr double KILO_ZETTA  = 1e-18;
    constexpr double KILO_EXA    = 1e-15;
    constexpr double KILO_PETA   = 1e-12;
    constexpr double KILO_TERA   = 1e-09;
    constexpr double KILO_GIGA   = 1e-06;
    constexpr double KILO_MEGA   = 1e-03;
    constexpr double KILO_HECTO  = 1e+01;
    constexpr double KILO_DECA   = 1e+02;
    constexpr double KILO_ONE    = 1e+03;
    constexpr double KILO_DECI   = 1e+04;
    constexpr double KILO_CENTI  = 1e+05;
    constexpr double KILO_MILLI  = 1e+06;
    constexpr double KILO_MICRO  = 1e+09;
    constexpr double KILO_NANO   = 1e+12;
    constexpr double KILO_PICO   = 1e+15;
    constexpr double KILO_FEMTO  = 1e+18;
    constexpr double KILO_ATTO   = 1e+21;
    constexpr double KILO_ZEPTO  = 1e+24;
    constexpr double KILO_YOCTO  = 1e+27;
    constexpr double HECTO_YOTTA = 1e-22;
    constexpr double HECTO_ZETTA = 1e-19;
    constexpr double HECTO_EXA   = 1e-16;
    constexpr double HECTO_PETA  = 1e-13;
    constexpr double HECTO_TERA  = 1e-10;
    constexpr double HECTO_GIGA  = 1e-07;
    constexpr double HECTO_MEGA  = 1e-04;
    constexpr double HECTO_KILO  = 1e-01;
    constexpr double HECTO_DECA  = 1e+01;
    constexpr double HECTO_ONE   = 1e+02;
    constexpr double HECTO_DECI  = 1e+03;
    constexpr double HECTO_CENTI = 1e+04;
    constexpr double HECTO_MILLI = 1e+05;
    constexpr double HECTO_MICRO = 1e+08;
    constexpr double HECTO_NANO  = 1e+11;
    constexpr double HECTO_PICO  = 1e+14;
    constexpr double HECTO_FEMTO = 1e+17;
    constexpr double HECTO_ATTO  = 1e+20;
    constexpr double HECTO_ZEPTO = 1e+23;
    constexpr double HECTO_YOCTO = 1e+26;
    constexpr double DECA_YOTTA  = 1e-23;
    constexpr double DECA_ZETTA  = 1e-20;
    constexpr double DECA_EXA    = 1e-17;
    constexpr double DECA_PETA   = 1e-14;
    constexpr double DECA_TERA   = 1e-11;
    constexpr double DECA_GIGA   = 1e-08;
    constexpr double DECA_MEGA   = 1e-05;
    constexpr double DECA_KILO   = 1e-02;
    constexpr double DECA_HECTO  = 1e-01;
    constexpr double DECA_ONE    = 1e+01;
    constexpr double DECA_DECI   = 1e+02;
    constexpr double DECA_CENTI  = 1e+03;
    constexpr double DECA_MILLI  = 1e+04;
    constexpr double DECA_MICRO  = 1e+07;
    constexpr double DECA_NANO   = 1e+10;
    constexpr double DECA_PICO   = 1e+13;
    constexpr double DECA_FEMTO  = 1e+16;
    constexpr double DECA_ATTO   = 1e+19;
    constexpr double DECA_ZEPTO  = 1e+22;
    constexpr double DECA_YOCTO  = 1e+25;
    constexpr double ONE_YOTTA   = 1e-24;
    constexpr double ONE_ZETTA   = 1e-21;
    constexpr double ONE_EXA     = 1e-18;
    constexpr double ONE_PETA    = 1e-15;
    constexpr double ONE_TERA    = 1e-12;
    constexpr double ONE_GIGA    = 1e-09;
    constexpr double ONE_MEGA    = 1e-06;
    constexpr double ONE_KILO    = 1e-03;
    constexpr double ONE_HECTO   = 1e-02;
    constexpr double ONE_DECA    = 1e-01;
    constexpr double ONE_DECI    = 1e+01;
    constexpr double ONE_CENTI   = 1e+02;
    constexpr double ONE_MILLI   = 1e+03;
    constexpr double ONE_MICRO   = 1e+06;
    constexpr double ONE_NANO    = 1e+09;
    constexpr double ONE_PICO    = 1e+12;
    constexpr double ONE_FEMTO   = 1e+15;
    constexpr double ONE_ATTO    = 1e+18;
    constexpr double ONE_ZEPTO   = 1e+21;
    constexpr double ONE_YOCTO   = 1e+24;
    constexpr double DECI_YOTTA  = 1e-25;
    constexpr double DECI_ZETTA  = 1e-22;
    constexpr double DECI_EXA    = 1e-19;
    constexpr double DECI_PETA   = 1e-16;
    constexpr double DECI_TERA   = 1e-13;
    constexpr double DECI_GIGA   = 1e-10;
    constexpr double DECI_MEGA   = 1e-07;
    constexpr double DECI_KILO   = 1e-04;
    constexpr double DECI_HECTO  = 1e-03;
    constexpr double DECI_DECA   = 1e-02;
    constexpr double DECI_ONE    = 1e-01;
    constexpr double DECI_CENTI  = 1e+01;
    constexpr double DECI_MILLI  = 1e+02;
    constexpr double DECI_MICRO  = 1e+05;
    constexpr double DECI_NANO   = 1e+08;
    constexpr double DECI_PICO   = 1e+11;
    constexpr double DECI_FEMTO  = 1e+14;
    constexpr double DECI_ATTO   = 1e+17;
    constexpr double DECI_ZEPTO  = 1e+20;
    constexpr double DECI_YOCTO  = 1e+23;
    constexpr double CENTI_YOTTA = 1e-26;
    constexpr double CENTI_ZETTA = 1e-23;
    constexpr double CENTI_EXA   = 1e-20;
    constexpr double CENTI_PETA  = 1e-17;
    constexpr double CENTI_TERA  = 1e-14;
    constexpr double CENTI_GIGA  = 1e-11;
    constexpr double CENTI_MEGA  = 1e-08;
    constexpr double CENTI_KILO  = 1e-05;
    constexpr double CENTI_HECTO = 1e-04;
    constexpr double CENTI_DECA  = 1e-03;
    constexpr double CENTI_ONE   = 1e-02;
    constexpr double CENTI_DECI  = 1e-01;
    constexpr double CENTI_MILLI = 1e+01;
    constexpr double CENTI_MICRO = 1e+04;
    constexpr double CENTI_NANO  = 1e+07;
    constexpr double CENTI_PICO  = 1e+10;
    constexpr double CENTI_FEMTO = 1e+13;
    constexpr double CENTI_ATTO  = 1e+16;
    constexpr double CENTI_ZEPTO = 1e+19;
    constexpr double CENTI_YOCTO = 1e+22;
    constexpr double MILLI_YOTTA = 1e-27;
    constexpr double MILLI_ZETTA = 1e-24;
    constexpr double MILLI_EXA   = 1e-21;
    constexpr double MILLI_PETA  = 1e-18;
    constexpr double MILLI_TERA  = 1e-15;
    constexpr double MILLI_GIGA  = 1e-12;
    constexpr double MILLI_MEGA  = 1e-09;
    constexpr double MILLI_KILO  = 1e-06;
    constexpr double MILLI_HECTO = 1e-05;
    constexpr double MILLI_DECA  = 1e-04;
    constexpr double MILLI_ONE   = 1e-03;
    constexpr double MILLI_DECI  = 1e-02;
    constexpr double MILLI_CENTI = 1e-01;
    constexpr double MILLI_MICRO = 1e+03;
    constexpr double MILLI_NANO  = 1e+06;
    constexpr double MILLI_PICO  = 1e+09;
    constexpr double MILLI_FEMTO = 1e+12;
    constexpr double MILLI_ATTO  = 1e+15;
    constexpr double MILLI_ZEPTO = 1e+18;
    constexpr double MILLI_YOCTO = 1e+21;
    constexpr double MICRO_YOTTA = 1e-30;
    constexpr double MICRO_ZETTA = 1e-27;
    constexpr double MICRO_EXA   = 1e-24;
    constexpr double MICRO_PETA  = 1e-21;
    constexpr double MICRO_TERA  = 1e-18;
    constexpr double MICRO_GIGA  = 1e-15;
    constexpr double MICRO_MEGA  = 1e-12;
    constexpr double MICRO_KILO  = 1e-09;
    constexpr double MICRO_HECTO = 1e-08;
    constexpr double MICRO_DECA  = 1e-07;
    constexpr double MICRO_ONE   = 1e-06;
    constexpr double MICRO_DECI  = 1e-05;
    constexpr double MICRO_CENTI = 1e-04;
    constexpr double MICRO_MILLI = 1e-03;
    constexpr double MICRO_NANO  = 1e+03;
    constexpr double MICRO_PICO  = 1e+06;
    constexpr double MICRO_FEMTO = 1e+09;
    constexpr double MICRO_ATTO  = 1e+12;
    constexpr double MICRO_ZEPTO = 1e+15;
    constexpr double MICRO_YOCTO = 1e+18;
    constexpr double NANO_YOTTA  = 1e-33;
    constexpr double NANO_ZETTA  = 1e-30;
    constexpr double NANO_EXA    = 1e-27;
    constexpr double NANO_PETA   = 1e-24;
    constexpr double NANO_TERA   = 1e-21;
    constexpr double NANO_GIGA   = 1e-18;
    constexpr double NANO_MEGA   = 1e-15;
    constexpr double NANO_KILO   = 1e-12;
    constexpr double NANO_HECTO  = 1e-11;
    constexpr double NANO_DECA   = 1e-10;
    constexpr double NANO_ONE    = 1e-09;
    constexpr double NANO_DECI   = 1e-08;
    constexpr double NANO_CENTI  = 1e-07;
    constexpr double NANO_MILLI  = 1e-06;
    constexpr double NANO_MICRO  = 1e-03;
    constexpr double NANO_PICO   = 1e+03;
    constexpr double NANO_FEMTO  = 1e+06;
    constexpr double NANO_ATTO   = 1e+09;
    constexpr double NANO_ZEPTO  = 1e+12;
    constexpr double NANO_YOCTO  = 1e+15;
    constexpr double PICO_YOTTA  = 1e-36;
    constexpr double PICO_ZETTA  = 1e-33;
    constexpr double PICO_EXA    = 1e-30;
    constexpr double PICO_PETA   = 1e-27;
    constexpr double PICO_TERA   = 1e-24;
    constexpr double PICO_GIGA   = 1e-21;
    constexpr double PICO_MEGA   = 1e-18;
    constexpr double PICO_KILO   = 1e-15;
    constexpr double PICO_HECTO  = 1e-14;
    constexpr double PICO_DECA   = 1e-13;
    constexpr double PICO_ONE    = 1e-12;
    constexpr double PICO_DECI   = 1e-11;
    constexpr double PICO_CENTI  = 1e-10;
    constexpr double PICO_MILLI  = 1e-09;
    constexpr double PICO_MICRO  = 1e-06;
    constexpr double PICO_NANO   = 1e-03;
    constexpr double PICO_FEMTO  = 1e+03;
    constexpr double PICO_ATTO   = 1e+06;
    constexpr double PICO_ZEPTO  = 1e+09;
    constexpr double PICO_YOCTO  = 1e+12;
    constexpr double FEMTO_YOTTA = 1e-39;
    constexpr double FEMTO_ZETTA = 1e-36;
    constexpr double FEMTO_EXA   = 1e-33;
    constexpr double FEMTO_PETA  = 1e-30;
    constexpr double FEMTO_TERA  = 1e-27;
    constexpr double FEMTO_GIGA  = 1e-24;
    constexpr double FEMTO_MEGA  = 1e-21;
    constexpr double FEMTO_KILO  = 1e-18;
    constexpr double FEMTO_HECTO = 1e-17;
    constexpr double FEMTO_DECA  = 1e-16;
    constexpr double FEMTO_ONE   = 1e-15;
    constexpr double FEMTO_DECI  = 1e-14;
    constexpr double FEMTO_CENTI = 1e-13;
    constexpr double FEMTO_MILLI = 1e-12;
    constexpr double FEMTO_MICRO = 1e-09;
    constexpr double FEMTO_NANO  = 1e-06;
    constexpr double FEMTO_PICO  = 1e-03;
    constexpr double FEMTO_ATTO  = 1e+03;
    constexpr double FEMTO_ZEPTO = 1e+06;
    constexpr double FEMTO_YOCTO = 1e+09;
    constexpr double ATTO_YOTTA  = 1e-42;
    constexpr double ATTO_ZETTA  = 1e-39;
    constexpr double ATTO_EXA    = 1e-36;
    constexpr double ATTO_PETA   = 1e-33;
    constexpr double ATTO_TERA   = 1e-30;
    constexpr double ATTO_GIGA   = 1e-27;
    constexpr double ATTO_MEGA   = 1e-24;
    constexpr double ATTO_KILO   = 1e-21;
    constexpr double ATTO_HECTO  = 1e-20;
    constexpr double ATTO_DECA   = 1e-19;
    constexpr double ATTO_ONE    = 1e-18;
    constexpr double ATTO_DECI   = 1e-17;
    constexpr double ATTO_CENTI  = 1e-16;
    constexpr double ATTO_MILLI  = 1e-15;
    constexpr double ATTO_MICRO  = 1e-12;
    constexpr double ATTO_NANO   = 1e-09;
    constexpr double ATTO_PICO   = 1e-06;
    constexpr double ATTO_FEMTO  = 1e-03;
    constexpr double ATTO_ZEPTO  = 1e+03;
    constexpr double ATTO_YOCTO  = 1e+06;
    constexpr double ZEPTO_YOTTA = 1e-45;
    constexpr double ZEPTO_ZETTA = 1e-42;
    constexpr double ZEPTO_EXA   = 1e-39;
    constexpr double ZEPTO_PETA  = 1e-36;
    constexpr double ZEPTO_TERA  = 1e-33;
    constexpr double ZEPTO_GIGA  = 1e-30;
    constexpr double ZEPTO_MEGA  = 1e-27;
    constexpr double ZEPTO_KILO  = 1e-24;
    constexpr double ZEPTO_HECTO = 1e-23;
    constexpr double ZEPTO_DECA  = 1e-22;
    constexpr double ZEPTO_ONE   = 1e-21;
    constexpr double ZEPTO_DECI  = 1e-20;
    constexpr double ZEPTO_CENTI = 1e-19;
    constexpr double ZEPTO_MILLI = 1e-18;
    constexpr double ZEPTO_MICRO = 1e-15;
    constexpr double ZEPTO_NANO  = 1e-12;
    constexpr double ZEPTO_PICO  = 1e-09;
    constexpr double ZEPTO_FEMTO = 1e-06;
    constexpr double ZEPTO_ATTO  = 1e-03;
    constexpr double ZEPTO_YOCTO = 1e+03;
    constexpr double YOCTO_YOTTA = 1e-48;
    constexpr double YOCTO_ZETTA = 1e-45;
    constexpr double YOCTO_EXA   = 1e-42;
    constexpr double YOCTO_PETA  = 1e-39;
    constexpr double YOCTO_TERA  = 1e-36;
    constexpr double YOCTO_GIGA  = 1e-33;
    constexpr double YOCTO_MEGA  = 1e-30;
    constexpr double YOCTO_KILO  = 1e-27;
    constexpr double YOCTO_HECTO = 1e-26;
    constexpr double YOCTO_DECA  = 1e-25;
    constexpr double YOCTO_ONE   = 1e-24;
    constexpr double YOCTO_DECI  = 1e-23;
    constexpr double YOCTO_CENTI = 1e-22;
    constexpr double YOCTO_MILLI = 1e-21;
    constexpr double YOCTO_MICRO = 1e-18;
    constexpr double YOCTO_NANO  = 1e-15;
    constexpr double YOCTO_PICO  = 1e-12;
    constexpr double YOCTO_FEMTO = 1e-09;
    constexpr double YOCTO_ATTO  = 1e-06;
    constexpr double YOCTO_ZEPTO = 1e-03;
  }
}

constexpr double operator""_yotta(long double value) {
  return value * Math::SI::YOTTA;
}
constexpr double operator""_zetta(long double value) {
  return value * Math::SI::ZETTA;
}
constexpr double operator""_exa(long double value) {
  return value * Math::SI::EXA;
}
constexpr double operator""_peta(long double value) {
  return value * Math::SI::PETA;
}
constexpr double operator""_tera(long double value) {
  return value * Math::SI::TERA;
}
constexpr double operator""_giga(long double value) {
  return value * Math::SI::GIGA;
}
constexpr double operator""_mega(long double value) {
  return value * Math::SI::MEGA;
}
constexpr double operator""_kilo(long double value) {
  return value * Math::SI::KILO;
}
constexpr double operator""_hecto(long double value) {
  return value * Math::SI::HECTO;
}
constexpr double operator""_deca(long double value) {
  return value * Math::SI::DECA;
}
constexpr double operator""_deci(long double value) {
  return value * Math::SI::DECI;
}
constexpr double operator""_centi(long double value) {
  return value * Math::SI::CENTI;
}
constexpr double operator""_milli(long double value) {
  return value * Math::SI::MILLI;
}
constexpr double operator""_micro(long double value) {
  return value * Math::SI::MICRO;
}
constexpr double operator""_nano(long double value) {
  return value * Math::SI::NANO;
}
constexpr double operator""_pico(long double value) {
  return value * Math::SI::PICO;
}
constexpr double operator""_femto(long double value) {
  return value * Math::SI::FEMTO;
}
constexpr double operator""_atto(long double value) {
  return value * Math::SI::ATTO;
}
constexpr double operator""_zepto(long double value) {
  return value * Math::SI::ZEPTO;
}
constexpr double operator""_yocto(long double value) {
  return value * Math::SI::YOCTO;
}

#endif
