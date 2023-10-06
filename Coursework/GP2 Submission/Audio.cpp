#include "Audio.h"

Audio::Audio()
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

Audio::~Audio()
{
    SDL_Quit();
}

void Audio::addSFX(const char* path)
{
    // Get SFX
    Mix_Chunk* SFX = Mix_LoadWAV(path);

    // If not found
    if (SFX == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize audio: %s", Mix_GetError());
        return;
    }
    
    // Add to list
    listOfEffects.push_back(SFX);
}

void Audio::addTrack(const char* path)
{
    // Load track
    backgroundTrack = Mix_LoadMUS(path);

    // Failed to load
    if (backgroundTrack == NULL)
    {
        std::cout << "Failed to load music. " << Mix_GetError();
    }
}

void Audio::playSFX(const int sfx) const
{
    // If effect is out of bounds
    if (sfx >= listOfEffects.size())
    {
        std::cout << "Invalid SFX.\n";
        return;
    }

    // Play SFX
    Mix_PlayChannel(1, listOfEffects[sfx], 0);
}

void Audio::playTrack()
{
    // If not playing
    if (Mix_PlayingMusic() == 0)
    {
        // Play Music
        Mix_PlayMusic(backgroundTrack, 1);
    }
}
