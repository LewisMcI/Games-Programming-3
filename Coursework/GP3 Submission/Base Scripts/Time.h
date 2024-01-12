#pragma once
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include <vector>

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
	void onUpdate();

private:
	Time();

	Uint64 currentTime;
	Uint64 lastTime;
	Uint64 startTime;
	double deltaTime;

	double fpsUpdateTime = 10.0f;
	double nextFPSUpdateTime = 0.0f;
	std::vector<double> fpsCounts;
	int fpsCountNum = 0;
};

