#pragma once

#include <memory>
#include <list>

#include "Subscriber.h"

namespace NPubSub {
    struct TPublisher {
        virtual ~TPublisher() {};

        SubscribeID Subscribe(
                const std::shared_ptr<ISubscriber>& subscriber
        );

        bool Unsubscribe(
                SubscribeID subscriberId
        );

        virtual void SendEvent(
                void* context
        );
    protected:
        std::list<std::shared_ptr<ISubscriber>> Subscribers;
    };
}