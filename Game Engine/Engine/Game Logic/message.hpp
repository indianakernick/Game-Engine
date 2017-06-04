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
    
    explicit Message(ID, Any = nullptr);
    ~Message() = default;
    
    ID id;
    Any data;
  };
  
  template <typename ID>
  class MessageManager;
  
  template <typename Id>
  class Messenger {
  public:
    using ID = Id;
  
    Messenger() = default;
    virtual ~Messenger() = default;
    
    void broadcastMessage(const Message message) {
      MessageManager<ID> *manager = getManager();
      assert(manager);
      manager->broadcastMessage(message);
    }
    void sendMessage(const ID dest, const Message message) {
      MessageManager<ID> *manager = getManager();
      assert(manager);
      manager->sendMessage(dest, message);
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
  private:
    static constexpr ID ALL_MESSENGERS = std::numeric_limits<ID>::max();
    
  public:
    MessageManager() = default;
    virtual ~MessageManager() = default;
    
    void broadcastMessage(const Message message) {
      messageQueue.emplace(ALL_MESSENGERS, message);
    }
    
    void sendMessage(const ID dest, const Message message) {
      messageQueue.emplace(dest, message);
    }
    
    void flushMessages() {
      while (!messageQueue.empty()) {
        const MessageWrapper &message = messageQueue.front();
        if (message.dest == ALL_MESSENGERS) {
          const ID numMessengers = getNumMessengers();
          for (ID i = 0; i != numMessengers; i++) {
            if (Messenger<ID> *messenger = getMessenger(i)) {
              messenger->onMessage(message.message);
            }
          }
        } else {
          Messenger<ID> *messenger = getMessenger(message.dest);
          if (messenger) {
            messenger->onMessage(message.message);
          } else {
            throw MissingMessenger("Tried to send a message to a Component that doesn't exist");
          }
        }
        messageQueue.pop();
      }
    }
  
  private:
    struct MessageWrapper {
      MessageWrapper(const ID dest, const Message message)
        : dest(dest), message(message) {}
      
      const ID dest;
      const Message message;
    };
    
    std::queue<MessageWrapper> messageQueue;
    
    //@TODO
    //try to think of a fast and generic interface that doesn't assume to
    //much about the actual container
    
    //this interface implicitly assumes vector
    
    virtual Messenger<ID> *getMessenger(ID) const = 0;
    virtual ID getNumMessengers() const = 0;
  };
};

#endif
