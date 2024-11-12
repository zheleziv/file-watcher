#pragma once

#include <cstdint>

namespace NPubSub {
    typedef uint64_t SubscribeID;

    struct ISubscriber {
        virtual ~ISubscriber() {};

        virtual uint64_t GetId() const {
            return (uint64_t)this;
        };

        // pure virtual function
        virtual void EventHandler(
                void* context
        ) = 0;
    };
}

