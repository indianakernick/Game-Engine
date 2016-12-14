//
//  xml.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "xml.hpp"

XML::InvalidDocument::InvalidDocument()
  : runtime_error("This XML document is invalid") {}

XML::NodePtr XML::makeNode(std::string name) {
  return std::make_shared<Node>(name);
}

XML::Node::Node(std::string name)
  : name(name) {}

std::string XML::Node::getName() {
  return name;
}

void XML::Node::setName(std::string newName) {
  assert(newName.size());
  name = newName;
}

std::string XML::Node::getAttrValue(std::string name) {
  auto iter = attributes.find(name);
  if (iter != attributes.end()) {
    return iter->second;
  } else {
    //not found
    return "";
  }
}

void XML::Node::setAttrVal(AttrKey key, AttrVal val) {
  attributes[key] = val;
}

size_t XML::Node::getAttrNum() {
  return attributes.size();
}

bool XML::Node::hasAttrs() {
  return !attributes.empty();
}

XML::Attrs &XML::Node::getAttributes() {
  return attributes;
}

XML::NodePtr XML::Node::getChildByName(std::string name) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    if ((*i)->name == name) {
      return *i;
    }
  }
  return nullptr;
}

void XML::Node::appendChild(NodePtr node) {
  if (hasContent()) {
    throw std::runtime_error("Cannot have text content and children");
  }
  children.push_back(node);
}

void XML::Node::prependChild(NodePtr node) {
  if (hasContent()) {
    throw std::runtime_error("Cannot have text content and children");
  }
  children.push_front(node);
}

size_t XML::Node::getChildNum() {
  return children.size();
}

bool XML::Node::hasChildren() {
  return !children.empty();
}

std::list<XML::NodePtr> &XML::Node::getChildren() {
  return children;
}

std::weak_ptr<XML::Node> XML::Node::getParent() {
  return parent;
}

std::string XML::Node::getContent() {
  return content;
}

void XML::Node::setContent(std::string newContent) {
  if (hasChildren()) {
    throw std::runtime_error("Cannot have text content and children");
  }
  content = newContent;
}

bool XML::Node::hasContent() {
  return children.empty() && !content.empty();
}

bool XML::Node::isEmpty() {
  return children.empty() && content.empty();
}

void XML::Node::write(std::ofstream &file, Format format) {
  file << "<?xml version=\"1.0\"?>\n";
  writeNode(file, format);
}

XML::NodePtr XML::Node::read(std::ifstream &file) {
  enum {
    NOTHING,
    OPEN_TAG,// <
    OPEN_SPECIAL_TAG,// ?
    CLOSE_SPECIAL_TAG,// ?
  } lastSaw = NOTHING;
  
  GET_CHAR:
  char c = file.get();
  
  if (std::isspace(c)) {
    goto GET_CHAR;
  }
  
  switch (lastSaw) {
    case NOTHING:
      if (c == '<') {
        lastSaw = OPEN_TAG;
        goto GET_CHAR;
      } else {
        throw InvalidDocument();
      }
    case OPEN_TAG:
      if (c == '?') {
        lastSaw = OPEN_SPECIAL_TAG;
        goto GET_CHAR;
      } else {
        //there isn't a special header with version and encoding
        file.seekg(0,std::ios::beg);
      }
    case OPEN_SPECIAL_TAG:
      if (c == '?') {
        lastSaw = CLOSE_SPECIAL_TAG;
      }
      goto GET_CHAR;
    case CLOSE_SPECIAL_TAG:
      if (c != '>') {
        throw InvalidDocument();
      }
  }
  
  return readNode(file);
}

XML::NodePtr XML::Node::readNode(std::ifstream &file) {
  NodePtr out = std::shared_ptr<Node>(new Node(""));
  
  enum {
    NOTHING,//inital state
    OPEN_TAG,// <
    CLOSE_TAG,// >
    TEXT_CONTENT,// some text
    OPEN_NEXT_TAG,// > before <
    NEXT_TAG_CLOSE,//the next tag is the closing tag for this tag. < before /
  } lastSaw = NOTHING;
  
  bool hasContent = false;//hasContent and hasChildren cannot both be true
  bool hasChildren = false;
  std::ios::pos_type nextTagPos = 0;//the position of the < of the next tag
  bool empty = false;
  
  GET_CHAR:
  char c = file.get();
  //ignore whitespace regardless of state
  if (std::isspace(c)) {
    goto GET_CHAR;
  } else if (c == EOF) {
    throw InvalidDocument();
  }
  
  switch (lastSaw) {
    case NOTHING:
      if (c == '<') {
        lastSaw = OPEN_TAG;
        out->name = readName(file);
        out->attributes = readAttrs(file);
        goto GET_CHAR;
      } else {
        throw InvalidDocument();
      }
    case OPEN_TAG:
      if (c == '/') {
        empty = true;
        goto GET_CHAR;
      } else if (c == '>') {
        if (empty) {
          return out;
        }
        lastSaw = CLOSE_TAG;
        goto GET_CHAR;
      }
    case CLOSE_TAG:
      if (c == '<') {
        //you can't perform arithmetic on pos_type
        file.seekg(-1,std::ios::cur);
        nextTagPos = file.tellg();
        file.seekg(1,std::ios::cur);
        
        lastSaw = OPEN_NEXT_TAG;
        goto GET_CHAR;
      } else {
        if (!hasChildren) {
          hasContent = true;
          file.seekg(-1, std::ios::cur);
          lastSaw = TEXT_CONTENT;
          goto GET_CHAR;
        } else {
          throw InvalidDocument();
        }
      }
    case TEXT_CONTENT:
      if (c == '<') {
        //you can't perform arithmetic on pos_type
        file.seekg(-1,std::ios::cur);
        nextTagPos = file.tellg();
        file.seekg(1,std::ios::cur);
        
        lastSaw = OPEN_NEXT_TAG;
        goto GET_CHAR;
      } else {
        out->content += c;
        goto GET_CHAR;
      }
      break;
    case OPEN_NEXT_TAG:
      if (c == '/') {
        lastSaw = NEXT_TAG_CLOSE;
        if (out->name != readName(file)) {
          throw InvalidDocument();
        }
        goto GET_CHAR;
      } else {
        if (!hasContent) {
          file.seekg(nextTagPos);
          out->children.push_back(readNode(file));
          hasChildren = true;
          lastSaw = CLOSE_TAG;
          goto GET_CHAR;
        } else {
          throw InvalidDocument();
        }
      }
    case NEXT_TAG_CLOSE:
      if (c == '>') {
        return out;
      } else {
        throw InvalidDocument();
      }
  }
}

std::string XML::Node::readName(std::ifstream &file) {
  std::string out;
  
  bool started = false;
  
  GET_CHAR:
  char c = file.get();
  if (std::isalpha(c)) {
    if (!started) {
      started = true;
    }
    out += c;
    goto GET_CHAR;
  } else {
    if (started) {
      file.seekg(-1, std::ios::cur);
      return out;
    } else {
      goto GET_CHAR;
    }
  }
}

XML::Attrs XML::Node::readAttrs(std::ifstream &file) {
  Attrs out;
  
  GET_CHAR:
  char c = file.get();
  if (std::isalpha(c)) {
    file.seekg(-1, std::ios::cur);
    out.emplace(readAttr(file));
    goto GET_CHAR;
  } else if (c == '/' || c == '>') {
    file.seekg(-1, std::ios::cur);
    return out;
  } else if (std::isspace(c)) {
    goto GET_CHAR;
  } else {
    throw InvalidDocument();
  }
}

XML::Attr XML::Node::readAttr(std::ifstream &file) {
  XML::Attr out;
  
  enum {
    NOTHING,
    KEY,
    EQUAL,
  } lastSaw = NOTHING;
  
  GET_CHAR:
  char c = file.get();
  
  switch (lastSaw) {
    case NOTHING:
      if (std::isspace(c)) {
        goto GET_CHAR;
      } else if (std::isalpha(c)) {
        file.seekg(-1, std::ios::cur);
        out.first = readAttrKey(file);
        lastSaw = KEY;
        goto GET_CHAR;
      } else {
        throw InvalidDocument();
      }
    case KEY:
      if (std::isspace(c)) {
        goto GET_CHAR;
      } else if (c == '=') {
        lastSaw = EQUAL;
        goto GET_CHAR;
      } else {
        throw InvalidDocument();
      }
    case EQUAL:
      if (std::isspace(c)) {
        goto GET_CHAR;
      } else if (c == '"') {
        file.seekg(-1, std::ios::cur);
        out.second = readAttrVal(file);
        return out;
      } else {
        throw InvalidDocument();
      }
  }
}

XML::AttrKey XML::Node::readAttrKey(std::ifstream &file) {
  return readName(file);
}

XML::AttrVal XML::Node::readAttrVal(std::ifstream &file) {
  AttrVal out;
  
  enum {
    NOTHING,
    OPEN_QUOTE,
  } lastSaw = NOTHING;
  
  GET_CHAR:
  char c = file.get();
  switch (lastSaw) {
    case NOTHING:
      if (std::isspace(c)) {
        goto GET_CHAR;
      } else if (c == '"') {
        lastSaw = OPEN_QUOTE;
        goto GET_CHAR;
      } else {
        throw InvalidDocument();
      }
    case OPEN_QUOTE:
      if (c == '"') {
        return out;
      } else {
        out += c;
        goto GET_CHAR;
      }
  }
}

void XML::Node::writeNode(std::ofstream &file, Format format) {
  std::string indentStr;
  if (format.use) {
    indentStr = std::string(format.indent * format.indentSize, ' ');
  }
  file << indentStr << '<' << name;
  for (auto i = attributes.begin(); i != attributes.end(); ++i) {
    file << ' ' << i->first << "=\"" << i->second << '"';
  }
  if (isEmpty()) {
    file << "/>\n";
  } else {
    file << '>';
    if (hasContent()) {
      file << content;
    } else {
      file << '\n';
      Format newFormat = {format.use, format.indentSize, format.indent + 1};
      for (auto i = children.begin(); i != children.end(); ++i) {
        (*i)->writeNode(file, newFormat);
      }
      file << indentStr;
    }
    file << "</" << name << ">\n";
  }
}
