#include "Time.h"

Time::Time() {
	// Initialize
	currentTime = 0;
	lastTime = 0;
	deltaTime = 0;
}

Time::~Time() {
	SDL_Quit();
}

// Returns deltaTime
double Time::getDeltaTime()
{
	return deltaTime;
}
Uint64 Time::getCurrentTime() {
	return SDL_GetTicks() / 1000.0;
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