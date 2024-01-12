#include "Time.h"
#include "../Other/GlobalVariables.h"
#include <iostream>

Time::Time() {
	// Initialize
	currentTime = 0;
	lastTime = 0;
	deltaTime = 0;
	startTime = SDL_GetPerformanceCounter();
}

double Time::getDeltaTime()
{
	return deltaTime;
}

double Time::getCurrentTime() {
	// Gets currentTime
	currentTime = SDL_GetPerformanceCounter();
	return (double)((currentTime - startTime) / (double)SDL_GetPerformanceFrequency());
}

// Calculated deltaTime using last and current time.
void Time::onUpdate() {
	// Sets lastTime to now
	lastTime = currentTime;

	// Gets currentTime
	currentTime = SDL_GetPerformanceCounter();

	// Calculate time since last frame.
	deltaTime = (double)((currentTime - lastTime) / (double)SDL_GetPerformanceFrequency());
	//std::cout << deltaTime * 1000.0f << std::endl;
	if (DEBUG_FPS) {
		fpsCounts.emplace_back(deltaTime * 1000.0f);
		fpsCountNum++;
		double currTime = getCurrentTime();
		if (nextFPSUpdateTime < currTime) {
			nextFPSUpdateTime = currTime + fpsUpdateTime;
			// Average
			double average = 0;
			for (size_t i = 0; i < fpsCountNum; i++)
			{
				average += fpsCounts[i];
			}
			average /= fpsCountNum - 1;
			std::cout << "Average FPS for past " << fpsUpdateTime << "[s] is: " << (double)1000.0f / average << " FPS" << std::endl;

			fpsCounts.clear();
			fpsCountNum = 0;
		}
	}
}