#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>

struct OnUpdateEvent {

};

class EventSystem {
public:
    template<typename EventType>
    void subscribe(std::function<void()> callback) {
        auto typeHash = typeid(EventType).hash_code();
        newSubscribedCallbacks_.push({ typeHash, callback });
    }

    template<typename EventType>
    void notify() {
        auto typeHash = typeid(EventType).hash_code();
        addNewSubscribedCallbacks();

        for (auto& callback : callbacks_[typeHash]) {
            callback();
        }
    }

private:
    struct NewCallback {
        size_t eventTypeHash;
        std::function<void()> callback;
    };

    void addNewSubscribedCallbacks() {
        while (!newSubscribedCallbacks_.empty()) {
            auto newCallback = newSubscribedCallbacks_.front();
            newSubscribedCallbacks_.pop();

            callbacks_[newCallback.eventTypeHash].push_back(newCallback.callback);
        }
    }

    std::unordered_map<size_t, std::vector<std::function<void()>>> callbacks_;
    std::queue<NewCallback> newSubscribedCallbacks_;
};
