#pragma once
#include <string>
#include "Component.h"

struct TagComponent : Component {
	std::string Tag;

	TagComponent() = default;
	TagComponent(const std::string& tag) 
		: Tag(tag) {}
};