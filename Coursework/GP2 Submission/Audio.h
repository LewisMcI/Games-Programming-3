#pragma once
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <iostream>
#include <vector>

class Audio
{
public:
	Audio();
	~Audio();

	void addSFX(const char* path);
	void addTrack(const char* path);
	void playSFX(const int which) const;
	void playTrack();

private:
	Mix_Music* backgroundTrack;
	std::vector<Mix_Chunk*> listOfEffects;
};
