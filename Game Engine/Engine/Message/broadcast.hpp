//
//  broadcast.hpp
//  Game Engine
//
//  Created by Indi Kernick on 29/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_message_broadcast_hpp
#define engine_message_broadcast_hpp

#include <forward_list>
#include <queue>
#include <cassert>

namespace Message {
  namespace Broadcast {
    struct Message {
      int id;
      void* data {nullptr};
    };
  
    class Com;
    
    class Pool {
    friend class Com;
    public:
      Pool(bool deleteComs = false);
      virtual ~Pool();
      
    protected:
      void add(Com*);
      void rem(Com*);
      ///Empty's the message queue
      void pump();
      void send(const Broadcast::Message&);
      
    private:
      bool deleteComs;
      std::forward_list<Com*> coms;
      struct Message {
        Broadcast::Message msg;
        Com* sender {nullptr};
      };
      std::queue<Message> msgs;
      //the coms call the private version so that the
      //message isn't sent to the sender
      void send(const Broadcast::Message&, Com* sender);
    };
    
    class Com {
    friend class Pool;
    public:
      Com() = default;
      virtual ~Com();
      
    protected:
      virtual void receive(const Broadcast::Message&) = 0;
      void send(const Broadcast::Message&);
      
    private:
      Pool* pool {nullptr};
    };
  };
}

#endif
