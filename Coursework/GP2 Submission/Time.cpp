#include "Time.h"

Time::Time() {
	// Initialize
	currentTime = 0;
	lastTime = 0;
	deltaTime = 0;
	startTime = SDL_GetPerformanceCounter();
}

Time::~Time() {
	SDL_Quit();
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
void Time::calculateDeltaTime() {
	// Sets lastTime to now
	lastTime = currentTime;

	// Gets currentTime
	currentTime = SDL_GetPerformanceCounter();

	// Calculate time since last frame.
	deltaTime = (double)((currentTime - lastTime) / (double)SDL_GetPerformanceFrequency());
}