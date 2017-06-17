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
  class AmbiguousID final : public std::invalid_argument {
  public:
    AmbiguousID(const std::string &parent, const std::string &child)
      : std::invalid_argument(
          "Node \"" + parent + "\" already has an child with ID \"" +
          child + "\". Children must have unique IDs"
        ) {}
  };
  
  class BadID final : public std::invalid_argument {
  public:
    explicit BadID(const std::string &id)
      : std::invalid_argument("The ID \"" + id + "\" is invalid") {}
  };
  
  class BadParentPtr final : public std::logic_error {
  public:
    explicit BadParentPtr(const std::string &what)
      : std::logic_error(what) {}
  };
  
  class NullChildPtr final : public std::invalid_argument {
  public:
    NullChildPtr()
      : std::invalid_argument("Child is a null pointer") {}
  };
  
  template <typename Derived>
  class NodeImpl {
  public:
    using DerivedPtr = std::shared_ptr<Derived>;
  
    NodeImpl() = default;
    virtual ~NodeImpl() = default;
    
    virtual void addChild(DerivedPtr) = 0;
    virtual void remChild(DerivedPtr) = 0;
    virtual void remAllChildren() = 0;
    virtual DerivedPtr getChild(std::experimental::string_view) const = 0;
    
    virtual Derived *getParentPtr() const = 0;
    virtual void setParentPtr(Derived *) = 0;
    virtual std::experimental::string_view getID() const = 0;
    
    virtual void forEachChild(const std::function<void (DerivedPtr)> &) = 0;
  
  private:
    static bool validFirstIDChar(const char c) {
      return std::isalpha(c);
    }

    static bool validIDChar(const char c) {
      return std::isalpha(c) || std::isdigit(c) || c == '_';
    }

  protected:
    static bool validID(const std::experimental::string_view id) {
      return
        id.size() &&
        validFirstIDChar(id[0]) &&
        std::all_of(id.cbegin() + 1, id.cend(), validIDChar)
      ;
    }
    
    static bool validID(const std::string &id) {
      return validID(std::experimental::string_view(id.data(), id.size()));
    }
    
    static bool validID(const char *id) {
      return validID(std::experimental::string_view(id));
    }
    
    static NodeImpl *getImpl(Derived * const node) {
      return node->impl.get();
    }
    
    static NodeImpl *getImpl(const DerivedPtr &node) {
      return node->impl.get();
    }
  };
  
  ///The Node base class. Users must provide an impl to the ctor.
  ///Node implements some error checking so that this isn't repeated in every impl
  template <typename Derived>
  class Node {
  public:
    friend class NodeImpl<Derived>;
  
    using DerivedPtr = std::shared_ptr<Derived>;
  
    explicit Node(std::unique_ptr<NodeImpl<Derived>> &&impl)
      : impl(std::move(impl)) {}
    virtual ~Node() {
      static_assert(std::is_base_of<Node, Derived>::value);
    }
    
    ///Add a child to the Node
    void addChild(const DerivedPtr child) {
      if (child == nullptr) {
        throw NullChildPtr();
      }
      Derived * const derivedThis = static_cast<Derived *>(this);
      Derived * const childParent = child->impl->getParentPtr();
      if (childParent == derivedThis) {
        throw BadParentPtr("Cannot add child to the parent more than once");
      } else if (childParent != nullptr) {
        throw BadParentPtr("Cannot add child to more than one parent");
      }
      impl->addChild(child);
      child->impl->setParentPtr(derivedThis);
    }
  
    ///Remove a child from the Node
    void remChild(const DerivedPtr child) {
      if (child == nullptr) {
        throw NullChildPtr();
      }
      if (child->impl->getParentPtr() != static_cast<Derived *>(this)) {
        throw BadParentPtr("Cannot remove child that is not a child of this Node");
      }
      impl->remChild(child);
      child->impl->setParentPtr();
    }
    
    ///Remove all child Nodes
    void remAllChildren() {
      impl->remAllChildren();
    }
    
    ///Get a child Node of the specified ID or nullptr if there isn't one
    DerivedPtr getChild(const std::experimental::string_view childID) const {
      return impl->getChild(childID);
    }
    
    ///Get a child Node of the specified ID cast to the specified class
    ///or nullptr if there isn't one
    template <typename DerivedClass>
    std::shared_ptr<DerivedClass> getChild(const std::experimental::string_view childID) const {
      return Utils::safeDownCast<DerivedClass>(getChild(childID));
    }

    ///Get the parent Node. Throws if there isn't one
    Derived &getParent() const {
      Derived *parent = impl->getParentPtr();
      if (parent == nullptr) {
        throw BadParentPtr("Tried to get the parent of a Node without a parent");
      } else {
        return *parent;
      }
    }
    
    ///Does this Node have a parent?
    bool hasParent() const {
      return impl->getParentPtr();
    }
    
    template <typename Function>
    void forEachChild(Function &&function) {
      impl->forEachChild(std::forward<Function>(function));
    }
    
  private:
    std::unique_ptr<NodeImpl<Derived>> impl;
  };
  
  ///Default implementation of NodeImpl
  template <typename Derived>
  class DefaultNodeImpl final : public NodeImpl<Derived> {
  private:
    using Base = NodeImpl<Derived>;
    
  public:
    using DerivedPtr = typename Base::DerivedPtr;
    using Children = std::list<DerivedPtr>;
  
    explicit DefaultNodeImpl(const std::string &id)
      : id(id) {
      if (!Base::validID(id)) {
        throw BadID(id);
      }
    }
    ~DefaultNodeImpl() = default;
    
    void addChild(const DerivedPtr child) override {
      const std::experimental::string_view childID = Base::getImpl(child)->getID();
      for (auto c = children.cbegin(); c != children.cend(); c++) {
        if (Base::getImpl(*c)->getID() == childID) {
          throw AmbiguousID(id, childID.to_string());
        }
      }
      children.push_front(child);
    }
    
    void remChild(const DerivedPtr child) override {
      children.remove(child);
    }
    
    void remAllChildren() override {
      children.remove_if([this] (const DerivedPtr &child) {
        Base::getImpl(child)->setParentPtr(nullptr);
        return true;
      });
    }
    
    DerivedPtr getChild(const std::experimental::string_view childID) const override {
      for (auto c = children.cbegin(); c != children.cend(); ++c) {
        if (Base::getImpl(*c)->getID() == childID) {
          return *c;
        }
      }
      
      return nullptr;
    }
    
    Derived *getParentPtr() const override {
      return parent;
    }
    
    void setParentPtr(Derived * const newParent) override {
      parent = newParent;
    }
    
    std::experimental::string_view getID() const override {
      return {id.data(), id.size()};
    }
    
    void forEachChild(const std::function<void (DerivedPtr)> &function) override {
      for (auto c = children.cbegin(); c != children.cend(); ++c) {
        function(*c);
      }
    }
    
  private:
    //@TODO If I never need to access the string ID of a Node I could
    //use a hash of the string instead.
    std::string id;
    Children children;
    Derived *parent = nullptr;
  };
}

#endif
