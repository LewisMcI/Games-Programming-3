#pragma once
#include <string>

struct TagComponent {
	std::string Tag;

	TagComponent() = default;
	TagComponent(const std::string& tag) 
		: Tag(tag) {}
};