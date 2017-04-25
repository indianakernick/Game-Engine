//
//  app.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app.hpp"

#include "search dir.hpp"
#include "write atlas.hpp"
#include "Image/load images.hpp"
#include "Image/pack images.hpp"
#include "Image/make image.hpp"
#include "Image/write image.hpp"
#include "Font/load font.hpp"
#include "Font/load glyphs.hpp"
#include <iostream>
#include <docopt/docopt.h>

static constexpr char USAGE[] = R"(Usage:
  atlasgen image [--output=<output_path>]
  atlasgen font --size=<point_size> --font=<font_path> [--output=<output_path>]
  atlasgen font [(--first=<bc> --last=<ec>) (--dpi_x=<h> --dpi_y=<v>)] --size=<point_size> --font=<font_path> [--output=<output_path>]

Options:
  --size=point_size        Size of the font in points
  --font=font_path         Path to the font file
  --output=output_path     Path to output file without an extension            [default: output]
  --first=fc               The first character in the range of characters      [default: 33]
  --last=lc                The last  character in the range of characters      [default: 126]
  --dpi_x=hori_dpi         The horizontal DPI of the display                   [default: 72]
  --dpi_y=vert_dpi         The vertial    DPI of the display                   [default: 72]
)";

ArgError::ArgError()
  : std::runtime_error("Invalid arguments") {}

void printBriefHelp() {
  std::cout << USAGE;
}

enum class Mode {
  IMAGE,
  FONT
};

Mode getMode(bool imageMode) {
  if (imageMode) {
    return Mode::IMAGE;
  } else {
    return Mode::FONT;
  }
}

void runImageMode(const std::string &workingDir, const std::string &outputPath) {
  std::remove((outputPath + ".png").c_str());
  
  std::vector<Image> images = loadImages(findFiles(workingDir));
  const int length = packImages(images);
  writeAtlas(outputPath + ".atlas", images, length);
  writeImage(outputPath + ".png", makeImage(images, length));
}

void runFontMode(
  const Font::Info &info,
  const std::string &fontPath,
  const std::string &outputPath
) {
  Glyphs glyphs = loadGlyphs(loadFont(fontPath, info));
  const int length = packImages(glyphs.images);
  writeAtlas(outputPath + ".atlas", glyphs, length);
  writeImage(outputPath + ".png", makeImage(glyphs.images, length));
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
  
  const Mode mode = getMode(options["image"].asBool());
  
  if (mode == Mode::IMAGE) {
    runImageMode(
      args[0].substr(0, args[0].find_last_of('/')),
      options["--output"].asString()
    );
  } else if (mode == Mode::FONT) {
    Font::Info info;
    info.pointSize = static_cast<int>(options["--size"].asLong());
    info.dpi.x     = static_cast<int>(options["--dpi_x"].asLong());
    info.dpi.y     = static_cast<int>(options["--dpi_y"].asLong());
    info.beginChar = static_cast<wchar_t>(options["--first"].asLong());
    info.endChar   = static_cast<wchar_t>(options["--last"].asLong() + 1);
    runFontMode(
      info,
      options["--font"].asString(),
      options["--output"].asString()
    );
  }
}
