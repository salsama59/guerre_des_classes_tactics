#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include "../src/menus/inventoryMenu.h"
#include "../src/game/game.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

InventoryMenu::InventoryMenu(Game &game)
{
    renderer = game.getRenderer();
    menuPosition.x = 0;
    menuPosition.y = 0;
    menuTexture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    MAXIMUM_SCREEN_WIDTH, MAXIMUM_SCREEN_HEIGHT);

    SDL_AudioSpec spec;
    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;
    int channelNumber = 4;
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 15) < 0)
    {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        exit(2);
    }
    else
    {
        Mix_QuerySpec(&spec.freq, &spec.format, &channelNumber);
        SDL_Log("Opened audio at %d Hz %d bit%s %s audio buffer\n", spec.freq,
                (spec.format & 0xFF),
                (SDL_AUDIO_ISFLOAT(spec.format) ? " (float)" : ""),
                (spec.channels > 2) ? "surround" : (spec.channels > 1) ? "stereo"
                                                                       : "mono");
    }

    /* Set the music volume */
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    Mix_Music *music = NULL;
    moveSound = Mix_LoadWAV("assets/sounds/deplacement.mp3");
    validationSound = Mix_LoadWAV("assets/sounds/validation.wav");
    cancelationSound = Mix_LoadWAV("assets/sounds/annulation.wav");
}

InventoryMenu::~InventoryMenu()
{
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(validationSound);
    Mix_FreeChunk(cancelationSound);
}

void InventoryMenu::displayInventory()
{
    bool isWaitingInputs = true;
    int trueTypeFontInitializationResult = 0;

    trueTypeFontInitializationResult = TTF_Init();

    if (trueTypeFontInitializationResult == -1)
    {
        fprintf(stderr, "An error occured during SDL_TTF initialization for the following reason : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }

    mainArialFont = TTF_OpenFont("assets/fonts/arial.ttf", 30);
    fontColor = {255, 255, 255};

    curssorPosition.w = 185;
    curssorPosition.h = 35;
    curssorPosition.x = 0;
    curssorPosition.y = 0;

    while (isWaitingInputs)
    {
        SDL_WaitEvent(&inputEvent);
        switch (inputEvent.type)
        {
        case SDL_QUIT:
            isWaitingInputs = false;
            exit(EXIT_SUCCESS);
            atexit(SDL_Quit);

        case SDL_KEYDOWN:
            switch (inputEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE: // Appui sur la touche Echap, on sort du menu pour revenir au jeu
                isWaitingInputs = false;
                break;

            case SDLK_SPACE:
                break;

            case SDLK_UP:

                break;

            case SDLK_DOWN:

                break;
            }
            break;
        }

        displayMenuElements();
    }
}

void InventoryMenu::displayMenuElements()
{
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, &menuPosition);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 36, 70);
    SDL_RenderFillRect(renderer, &curssorPosition);

    SDL_RenderPresent(renderer);
}
