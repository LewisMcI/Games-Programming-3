#include "AudioManager.h"
#include "Other/GlobalVariables.h"

AudioManager::AudioManager()
{
    // Iniialize local variables
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    // Create audio source - If fails logs and exits.
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize audio: %s", Mix_GetError());
        exit(-1);
    }
}

void AudioManager::playSFX(AudioType audioType)
{
    // If SFX not loaded
    if (!loadedSFX.count(audioType)) {
        // Get SFX
        Mix_Chunk* SFX = Mix_LoadWAV(sfxPaths[audioType].c_str());

        // If not found
        if (SFX == nullptr) {
            if (USE_ERROR_DEBUGGING)
                std::cout << "Failed to load SFX at path: " << sfxPaths[audioType] << Mix_GetError() << std::endl;
            return;
        }

        // Add to list
        loadedSFX.emplace(audioType, SFX);
    }

    Mix_PlayChannel(1, loadedSFX[audioType], 0);
}

void AudioManager::playTrack(TrackType trackType)
{
    // If Track not loaded
    if (!loadedTracks.count(trackType)) {
        // Get track
        Mix_Music* backgroundTrack = Mix_LoadMUS(trackPaths[trackType].c_str());

        // If not found
        if (backgroundTrack == NULL){
            if (USE_ERROR_DEBUGGING)
                std::cout << "Failed to load Track at path: " << trackPaths[trackType] << Mix_GetError() << std::endl;
            return;
        }

        // Add to list
        loadedTracks.emplace(trackType, backgroundTrack);
    }


    // If not playing
    if (Mix_PlayingMusic() == 0)
    {
        // Play Music
        Mix_PlayMusic(loadedTracks[trackType], 1);
    }
}