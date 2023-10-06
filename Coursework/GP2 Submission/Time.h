#pragma once

#include <SDL\SDL.h>

class Time
{
public:
	Time();
	~Time();

	double getDeltaTime();
	Uint64 getCurrentTime();
private:
	void calculateDeltaTime();
	Uint64 currentTime;
	Uint64 lastTime;
	double deltaTime;
};

