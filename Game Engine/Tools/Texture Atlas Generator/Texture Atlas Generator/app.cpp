//
//  app.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app.hpp"

#include "Font/user interface.hpp"
#include "Image/user interface.hpp"
#include <iostream>
#include <docopt/docopt.h>

static constexpr char USAGE[] = R"(Usage:
  atlasgen image [--input=<input_path> --whitepixel=<px> --sep=<px> --output=<output_path>]
  atlasgen font --font=<font_path> --points=<point_size> [--output=<output_path>]
  atlasgen font --font=<font_path> --points=<point_size> [--sep=<px> (--first=<fc> --last=<lc>) (--dpi_x=<x> --dpi_y=<y>) --output=<output_path>]

Options:
  -f --font=font_path         Path to the font file
  -p --points=point_size      Point size of the font
  -w --whitepixel=px          Radius of the white pixel                         [default: -1]
  -s --sep=px                 The number of pixels separating each image        [default: 1]
  -i --input=input_path       Path to directory to find images                  [default: .]
  -o --output=output_path     Path to output file without an extension          [default: output]
  --dpi_x=hori_dpi            Horizontal DPI                                    [default: 96]
  --dpi_y=vert_dpi            Vertical DPI                                      [default: 96]
  --first=first_char          ASCII Codepoint of the first character            [default: 32]
  --last=last_char            ASCII Codepoint of the last character             [default: 126]
)";

ArgError::ArgError()
  : std::runtime_error("Invalid arguments") {}

using namespace std::literals;

InvalidArgVal::InvalidArgVal(const char *what)
  : std::runtime_error("Invalid argument value: "s + what) {}

void printBriefHelp() {
  std::cout << USAGE;
}

template <typename DST, typename SRC>
DST safeIntCast(const SRC src, const char *errMsg) {
  if (std::numeric_limits<DST>::min() <= src && src <= std::numeric_limits<DST>::max()) {
    return static_cast<DST>(src);
  } else {
    throw InvalidArgVal(errMsg);
  }
}

void runApp(const std::vector<std::string> &args) {
  if (args.size() == 1) {
    throw ArgError();
  }
  
  std::map<std::string, docopt::value> options;
  
  try {
    options = docopt::docopt_parse(USAGE, {args.cbegin() + 1, args.cend()});
  } catch (docopt::DocoptArgumentError &e) {
    std::cerr << "Argument error: " << e.what() << '\n';
    throw ArgError();
  } catch (docopt::DocoptLanguageError &e) {
    std::cerr << "Language Error: " << e.what() << '\n';
    throw std::runtime_error("");
  }
  
  /*for (const auto &o : options) {
    std::cout << o.first << ":  " << o.second << '\n';
  }*/
  
  if (options["image"].asBool()) {
    createImageAtlas(
      options["--input"].asString(),
      options["--output"].asString(),
      safeIntCast<int>(options["--whitepixel"].asLong(), "whitepixel must a reasonable value"),
      safeIntCast<unsigned>(options["--sep"].asLong(), "sep must be a positive integer")
    );
  } else {
    const char first = safeIntCast<char>(options["--first"].asLong(), "first must be an ASCII codepoint");
    const char last = safeIntCast<char>(options["--last"].asLong(), "last must be an ASCII codepoint");
    if (first > last) {
      throw InvalidArgVal("first must be less than or equal to last");
    }
    createFontAtlas(
      options["--font"].asString(),
      options["--output"].asString(),
      {
        safeIntCast<unsigned>(options["--points"].asLong(), "points must be a positive integer"),
        {
          safeIntCast<unsigned>(options["--dpi_x"].asLong(), "dpi_x must be a positive integer"),
          safeIntCast<unsigned>(options["--dpi_y"].asLong(), "dpi_y must be a positive integer")
        }
      },
      //32 is space. before space is control characters
      first < 32 ? 32 : first,
      //127 is delete
      last == 127 ? 127 : last + 1,
      safeIntCast<unsigned>(options["--sep"].asLong(), "sep must be a positive integer")
    );
  }
}
