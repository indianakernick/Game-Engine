//
//  message.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_message_hpp
#define engine_game_logic_message_hpp

#include <queue>
#include "../Utils/any.hpp"

namespace Game {
  class Message {
  public:
    using ID = uint32_t;
    
    explicit Message(ID, const Any & = nullptr);
    explicit Message(ID, Any && = nullptr);
    ~Message() = default;
    
    Any data;
    ID id;
  };
  
  template <typename ID>
  class MessageManager;
  
  template <typename Id>
  class Messenger {
  public:
    using ID = Id;
  
    Messenger() = default;
    virtual ~Messenger() = default;
    
    void sendMessage(const ID dest, const Message &message) {
      MessageManager<ID> *manager = getManager();
      assert(manager);
      manager->sendMessage(dest, message);
    }
    
    void sendMessage(const ID dest, Message &&message) {
      MessageManager<ID> *manager = getManager();
      assert(manager);
      manager->sendMessage(dest, std::move(message));
    }
    
    virtual void onMessage(Message) = 0;
  
  private:
    virtual MessageManager<ID> *getManager() const = 0;
  };
  
  class MissingMessenger final : public std::runtime_error {
  public:
    explicit MissingMessenger(const char *);
  };
  
  template <typename ID>
  class MessageManager {
  public:
    MessageManager() = default;
    virtual ~MessageManager() = default;
    
    void sendMessage(const ID dest, const Message &message) {
      messageQueue.emplace(dest, message);
    }
    
    void sendMessage(const ID dest, Message &&message) {
      messageQueue.emplace(dest, std::move(message));
    }
    
    void flushMessages() {
      while (!messageQueue.empty()) {
        const MessageWrapper &message = messageQueue.front();
        Messenger<ID> *messenger = getMessenger(message.dest);
        if (messenger) {
          messenger->onMessage(std::move(message.message));
        } else {
          throw MissingMessenger("Tried to send a message to a Component that doesn't exist");
        }
        messageQueue.pop();
      }
    }
  
  private:
    struct MessageWrapper {
      MessageWrapper(const ID dest, const Message &message)
        : message(message), dest(dest) {}
      MessageWrapper(const ID dest, Message &&message)
        : message(std::move(message)), dest(dest) {}
      
      const Message message;
      const ID dest;
    };
    
    std::queue<MessageWrapper> messageQueue;
    
    virtual Messenger<ID> *getMessenger(ID) const = 0;
  };
};

#endif
