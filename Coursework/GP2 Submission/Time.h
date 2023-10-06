#pragma once

#include <SDL\SDL.h>

class Time
{
public:
	Time();
	~Time();

	double getDeltaTime();
	double getCurrentTime();
private:
	void calculateDeltaTime();
	Uint64 currentTime;
	Uint64 lastTime;
	Uint64 startTime;
	double deltaTime;
};

