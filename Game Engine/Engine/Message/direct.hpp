//
//  direct.hpp
//  Game Engine
//
//  Created by Indi Kernick on 29/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef direct_hpp
#define direct_hpp

#include <unordered_map>
#include <queue>
#include <assert.h>

namespace Message {
  namespace Direct {
    struct Message {
      int id;
      void* data;
    };
  
    class Com;
    
    class Pool {
    friend class Com;
    public:
      Pool(bool deleteComs = false);
      virtual ~Pool();
      
    protected:
      void add(int id, Com*);
      void rem(int id);
      ///Empty's the message queue
      void pump();
      void send(const Direct::Message&, int receiverID);
      
    private:
      bool deleteComs;
      std::unordered_map<int, Com*> coms;
      struct Message {
        Direct::Message msg;
        int receiverID;
      };
      std::queue<Message> msgs;
    };
    
    class Com {
    friend class Pool;
    public:
      Com() = default;
      virtual ~Com();
      
    protected:
      virtual void recieve(const Direct::Message&) = 0;
      void send(const Direct::Message&, int receiverID);
      int getID();
      
    private:
      int id;
      Pool* pool {nullptr};
    };
  }
}

#endif
