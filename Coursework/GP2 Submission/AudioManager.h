#pragma once
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>

enum class AudioType { Fire, Explosion };
enum class TrackType { Background };
class AudioManager
{
public:
	AudioManager();
	~AudioManager() {
		SDL_Quit();
	}

	static AudioManager& getInstance() {
		static AudioManager instance;
		return instance;
	}

	void playSFX(AudioType audioType);

	void playTrack(TrackType trackType);

private:
	/* SFX*/
	// Map of Audio Type and Audio Paths
	std::map<AudioType, std::string> sfxPaths = {
			{AudioType::Fire, "..\\Resources\\Audio\\fire.wav"},
			{AudioType::Explosion, "..\\Resources\\Audio\\explosion.wav"}
	};

	// Map of AudioType and Loaded Audio
	std::map<AudioType, Mix_Chunk*> loadedSFX;


	/* Tracks*/
	// Map of Track Type and Track Paths
	std::map<TrackType, std::string> trackPaths = {
			{TrackType::Background, "..\\Resources\\Audio\\background.wav"}
	};

	// Map of TrackType and Loaded Meshes
	std::map<TrackType, Mix_Music*> loadedTracks;
};
