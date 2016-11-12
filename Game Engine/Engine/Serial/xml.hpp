//
//  xml.hpp
//  game engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef xml_hpp
#define xml_hpp

#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <cassert>
#include "whitespace.hpp"
#include "alphabetchar.hpp"

namespace XML {
  class InvalidDocument : public std::runtime_error {
  public:
    InvalidDocument();
  };
  
  class Node;
  typedef std::shared_ptr<Node> NodePtr;
  typedef std::weak_ptr<Node> WeakNodePtr;
  typedef std::string AttrKey;
  typedef std::string AttrVal;
  typedef std::map<AttrKey, AttrVal> Attrs;
  typedef std::pair<AttrKey, AttrVal> Attr;

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
    std::list<NodePtr> &getChildren();
    
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
    std::list<NodePtr> children;
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