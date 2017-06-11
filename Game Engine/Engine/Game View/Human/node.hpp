//
//  node.hpp
//  Game Engine
//
//  Created by Indi Kernick on 3/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_node_hpp
#define engine_game_view_human_node_hpp

#include <list>
#include <cctype>
#include <string>
#include <memory>
#include <experimental/string_view>
#include "../../Utils/safe down cast.hpp"

namespace UI {
  template <typename Derived>
  class Node {
  private:
    using DerivedPtr = std::shared_ptr<Derived>;
    
  public:
    class AmbiguousID final : public std::runtime_error {
    public:
      AmbiguousID(const std::string &parent, const std::string &child)
        : std::runtime_error("Element \"" + parent + "\" already has an child with ID \"" + child + "\". Children must have unique IDs") {}
    };
    
    class BadID final : public std::runtime_error {
    public:
      explicit BadID(const std::string &id)
        : std::runtime_error("The ID \"" + id + "\" is invalid") {}
    };
    
    class BadParentPtr final : public std::runtime_error {
    public:
      explicit BadParentPtr(const std::string &what)
        : std::runtime_error(what) {}
    };
  
    using Children = std::list<DerivedPtr>;
  
    explicit Node(const std::string &id)
      : id(id), derivedThis(static_cast<Derived *>(this)) {
      if (!validID(id)) {
        throw BadID(id);
      }
    }
    virtual ~Node() {
      static_assert(std::is_base_of<Node, Derived>::value);
    }
    
    void addChild(const DerivedPtr child) {
      assert(child);
      if (child->parent == derivedThis) {
        throw BadParentPtr("Cannot add the child \"" + child->id + "\" to the parent \"" + id + "\" more than once");
      } else if (child->parent != nullptr) {
        throw BadParentPtr("Cannot add the child \"" + child->id + "\" to more than one parent");
      }
      for (auto c = children.cbegin(); c != children.cend(); c++) {
        if ((*c)->id == child->id) {
          throw AmbiguousID(id, child->id);
        }
      }
      children.push_front(child);
      child->parent = derivedThis;
    }
    
    void remChild(const DerivedPtr child) {
      assert(child);
      if (child->parent != derivedThis) {
        throw BadParentPtr("Cannot remove child \"" + child->id + "\" that is not a child of this Node");
      }
      children.remove(child);
      child->parent = nullptr;
    }
    
    void remAllChildren() {
      children.remove_if([this](DerivedPtr child) {
        child->parent = nullptr;
        return true;
      });
    }
    
    const Children &getChildren() const {
      return children;
    }
    
    DerivedPtr getChild(std::experimental::string_view childPath) const {
      const size_t nextIDPos = childPath.find_first_of('/') + 1;
      if (nextIDPos == 1) {
        throw BadID(childPath.to_string());
      }
      const std::experimental::string_view childID =
        nextIDPos == 0
        ? childPath
        : std::experimental::string_view(childPath.data(), nextIDPos)
      ;
      for (auto c = children.cbegin(); c != children.cend(); ++c) {
        if ((*c)->id == childID) {
          if (nextIDPos == 0) {
            return *c;
          } else {
            return (*c)->getChild({
              childPath.data() + nextIDPos,
              childPath.size() - nextIDPos - 1
            });
          }
        }
      }
      
      return nullptr;
    }
    
    template <typename DerivedClass>
    std::shared_ptr<DerivedClass> getChild(const std::experimental::string_view childID) const {
      return Utils::safeDownCast<DerivedClass>(getChild(childID));
    }

    Derived &getParent() const {
      if (parent == nullptr) {
        throw BadParentPtr("Tried to get the parent of \"" + id + "\" which doesn't have a parent");
      }
      return *parent;
    }

    bool hasParent() const {
      return parent;
    }
    
  private:
    //@TODO If I never need to access the string ID of a Node I could
    //use a hash of the string instead.
    std::string id;
    Children children;
    Derived *parent = nullptr;
    Derived * const derivedThis;
    
    static bool validFirstIDChar(const char c) {
      return std::isalpha(c);
    }

    static bool validIDChar(const char c) {
      return std::isalpha(c) || std::isdigit(c) || c == '_';
    }

    static bool validID(const std::string &id) {
      return
        id.size() &&
        validFirstIDChar(id[0]) &&
        std::all_of(id.cbegin() + 1, id.cend(), validIDChar)
      ;
    }
  };
}

#endif
