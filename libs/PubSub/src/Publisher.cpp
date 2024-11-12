#include "PubSub/Publisher.h"

#include <algorithm>

using namespace NPubSub;

uint64_t TPublisher::Subscribe(const std::shared_ptr<ISubscriber>& subscriber) {
    auto findIter = std::find_if(
            Subscribers.begin(),
            Subscribers.end(),
            [subscriber](const std::shared_ptr<ISubscriber>& s) {
                return s->GetId() == subscriber->GetId();
            }
    );

    if(findIter != Subscribers.end())
        return 0;

    Subscribers.push_back(subscriber);
    return subscriber->GetId();
}

bool TPublisher::Unsubscribe(uint64_t subscriberId) {
    auto findIter = std::find_if(
            Subscribers.begin(),
            Subscribers.end(),
            [subscriberId](const std::shared_ptr<ISubscriber>& s) {
                return s->GetId() == subscriberId;
            }
    );

    if(findIter != Subscribers.end()){
        Subscribers.erase(findIter);
        return true;
    }
    return false;
}

void TPublisher::SendEvent(void *context) {
    for(auto& subscriber : Subscribers) {
        subscriber->EventHandler(context);
    }
}
