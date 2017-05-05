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
  atlasgen image [--input=<input_path> --output=<output_path>]
  atlasgen font --font=<font_path> --options=<options_path> [--output=<output_path>]

Options:
  -i --input=input_path       Path to directory to find images          [default: .]
  -o --output=output_path     Path to output file without an extension  [default: output]
  -f --font=font_path         Path to the font file
  --options=options_path      Path to options file
)";

ArgError::ArgError()
  : std::runtime_error("Invalid arguments") {}

void printBriefHelp() {
  std::cout << USAGE;
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
  
  for (const auto &o : options) {
    std::cout << o.first << ":  " << o.second << '\n';
  }
  
  if (options["image"].asBool()) {
    createAtlasFromDir(
      options["--input"].asString(),
      options["--output"].asString()
    );
  } else {
    createAtlasFromOptionsFile(
      options["--options"].asString(),
      options["--font"].asString(),
      options["--output"].asString()
    );
  }
}
