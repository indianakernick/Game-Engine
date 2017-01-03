//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

bool Resource::Loaders::XML::canLoad(const std::string &fileExt) {
  return fileExt == "xml";
}

//this resource cache is proving to be rather inflexable

//it can't handle custom allocation. it allocates the memory and hands it to
//the loader. Storing an XML document in one contigous block of memory
//would require a custom memory manager. tinyxml2 has its own memory manager
//but doesn't allow the use of a custom memory manager.
//i dont want to edit the library

//another thing missing from tinyxml2 is a function to traverse the document
//and count the number of bytes in use. That way i could at least limit
//the size of the cache

//i could have a guess and say the allocation size is a bit bigger than the file
//because an xml document is mostly text so all that text from the file will
//be in the DOM. but if getSize returned a number greater than zero the cache
//would allocation that amount

size_t Resource::Loaders::XML::getSize(const Memory::Buffer) {
  return 0;
}

bool Resource::Loaders::XML::useRaw() {
  return false;
}

Resource::Desc::Ptr Resource::Loaders::XML::process(const Memory::Buffer file, Memory::Buffer) {
  std::shared_ptr<tinyxml2::XMLDocument> document = std::make_shared<tinyxml2::XMLDocument>();
  document->Parse(reinterpret_cast<const char *>(file.begin()), file.size());
  document->PrintError();
  return std::make_shared<Descs::XML>(document);
}
