#pragma once
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>

class Time
{
public:
	static Time& getInstance()
	{
		static Time instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	double getDeltaTime();
	double getCurrentTime();
	void Update();

private:
	Time();

	Uint64 currentTime;
	Uint64 lastTime;
	Uint64 startTime;
	double deltaTime;
};

