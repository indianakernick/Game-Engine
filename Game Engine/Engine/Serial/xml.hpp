//
//  xml.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_serial_xml_hpp
#define engine_serial_xml_hpp

#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <cassert>
#include <cctype>

namespace XML {
  class InvalidDocument : public std::runtime_error {
  public:
    InvalidDocument();
  };
  
  class Node;
  using NodePtr = std::shared_ptr<Node>;
  using WeakNodePtr = std::weak_ptr<Node>;
  using AttrKey = std::string;
  using AttrVal = std::string;
  using Attrs = std::map<AttrKey, AttrVal>;
  using Attr = std::pair<AttrKey, AttrVal>;
  using Children = std::list<NodePtr>;

  NodePtr makeNode(std::string name);

  class Node {
  public:
    Node(std::string name);
  
    std::string getName();
    void setName(std::string);
    
    AttrVal getAttrValue(AttrKey);
    void setAttrVal(AttrKey, AttrVal);
    size_t getAttrNum();
    bool hasAttrs();
    Attrs &getAttributes();
    
    NodePtr getChildByName(std::string);
    void appendChild(NodePtr);
    void prependChild(NodePtr);
    size_t getChildNum();
    bool hasChildren();
    Children &getChildren();
    
    WeakNodePtr getParent();
    
    std::string getContent();
    void setContent(std::string);
    bool hasContent();
    
    bool isEmpty();
    
    struct Format {
      bool use;
      int indentSize;
      int indent;
    };
    
    void write(std::ofstream &, Format = {0,0,0});
    static NodePtr read(std::ifstream &);
  private:
    WeakNodePtr parent;
    std::string name;
    Attrs attributes;
    Children children;
    std::string content;
    
    static NodePtr readNode(std::ifstream &);
    static std::string readName(std::ifstream &);
    
    static Attrs readAttrs(std::ifstream &);
    static Attr readAttr(std::ifstream &);
    static AttrKey readAttrKey(std::ifstream &);
    static AttrVal readAttrVal(std::ifstream &);
    
    void writeNode(std::ofstream &, Format);
  };
};

#endif
