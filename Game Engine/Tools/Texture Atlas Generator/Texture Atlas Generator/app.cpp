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
  atlasgen image [-i<path> -w<px> -s<px> -o<path>]
  atlasgen font -f<path> -p<int> [-s<px> (-F<cp> -L<cp>) (-x<int> -y<int>) -o<path>]

Options:
  -f --font=path              Path to the font file
  -p --points=int             Point size of the font
  -w --whitepixel=px          Radius of the white pixel                         [default: -1]
  -s --sep=px                 The number of pixels separating each image        [default: 1]
  -i --input=path             Path to directory to find images                  [default: .]
  -o --output=path            Path to output file without an extension          [default: output]
  -x --dpi_x=int              Horizontal DPI                                    [default: 96]
  -y --dpi_y=int              Vertical DPI                                      [default: 96]
  -F --first=codepoint        ASCII Codepoint of the first character            [default: 32]
  -L --last=codepoint         ASCII Codepoint of the last character             [default: 126]
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
      safeIntCast<SizePx>(options["--whitepixel"].asLong(), "whitepixel must a reasonable value"),
      safeIntCast<SizePx>(options["--sep"].asLong(), "sep must be a positive integer")
    );
  } else {
    const CodePoint first = safeIntCast<CodePoint>(options["--first"].asLong(), "first must be an ASCII codepoint");
    const CodePoint last = safeIntCast<CodePoint>(options["--last"].asLong(), "last must be an ASCII codepoint");
    if (first > last) {
      throw InvalidArgVal("first must be less than or equal to last");
    }
    createFontAtlas(
      options["--font"].asString(),
      options["--output"].asString(),
      {
        {
          safeIntCast<SizePx>(options["--dpi_x"].asLong(), "dpi_x must be a positive integer"),
          safeIntCast<SizePx>(options["--dpi_y"].asLong(), "dpi_y must be a positive integer")
        },
        safeIntCast<SizePt>(options["--points"].asLong(), "points must be a positive integer")
      },
      {
        first < ' ' ? ' ' : first,
        //127 is delete
        static_cast<CodePoint>(last == 127 ? 127 : last + 1),
      },
      safeIntCast<SizePx>(options["--sep"].asLong(), "sep must be a positive integer")
    );
  }
}
