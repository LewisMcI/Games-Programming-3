#pragma once
#include <string>
#include "Component.h"

struct TagComponent : public Component {
	std::string Tag;

	TagComponent() = default;
	TagComponent(const std::string& tag) 
		: Tag(tag) {}
};