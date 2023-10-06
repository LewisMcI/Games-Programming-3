#pragma once

#include <SDL\SDL.h>

class Time
{
public:
	Time();
	~Time();

	void calculateDeltaTime();
	double getDeltaTime();
private:
	Uint64 currentTime;
	Uint64 lastTime;
	double deltaTime;
};

