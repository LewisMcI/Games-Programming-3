#pragma once
#include <functional>
struct OnUpdateEvent {

};
class EventSystem {
public:
	template<typename EventType>
	void subscribe(std::function<void()> callback) {
		auto typeHash = typeid(EventType).hash_code();
		callbacks_[typeHash].push_back(callback);
	}

	template<typename EventType>
	void notify() {
		auto typeHash = typeid(EventType).hash_code();
		for (auto& callback : callbacks_[typeHash]) {
			callback();
		}
	}
private:
	std::unordered_map<size_t, std::vector<std::function<void()>>> callbacks_;
};