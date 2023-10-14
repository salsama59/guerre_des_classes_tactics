#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ft2build.h>
#include "partyMenu.h"
#include "game.h"
#include "spear.h"
#include "glove.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

PartyMenu::PartyMenu(SDL_Renderer *renderer)
{
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
    moveSound = Mix_LoadWAV("deplacement.mp3");
    validationSound = Mix_LoadWAV("validation.wav");
    cancelationSound = Mix_LoadWAV("annulation.wav");
}

PartyMenu::~PartyMenu()
{
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(validationSound);
    Mix_FreeChunk(cancelationSound);
}

void PartyMenu::displayPartyMenu(std::vector<Character *> party, std::vector<Character *> team, SDL_Renderer *renderer, Game *game)
{
    int trueTypeFontInitializationResult = 0, teamSize = 0, memberIndex = 0;
    bool isWaitingInputs = true;
    teamSize = team.size();
    int maximumHitPoints[teamSize], maximumMagicPoints[teamSize], hitPoints[teamSize], magicPoints[teamSize], levels[teamSize];
    string prenom[teamSize];
    trueTypeFontInitializationResult = TTF_Init();
    if (trueTypeFontInitializationResult == -1)
    {
        fprintf(stderr, "An error occured during SDL_TTF initialization for the following reason : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }
    mainArialFont = TTF_OpenFont("arial.ttf", 30);
    secondaryArialFont = TTF_OpenFont("arial.ttf", 20);
    fontColor = {255, 255, 255};
    equipmentBonusFontColor = {255, 255, 0};

    curssorPosition.w = MAXIMUM_SCREEN_WIDTH / 2;
    curssorPosition.h = 100;
    curssorPosition.x = 0;
    curssorPosition.y = 45;

    for (int i = 0; i < teamSize; i++)
    {
        int statTextWidth = 0;
        int statTextHeight = 0;
        characterPortraitSpriteSheetTexturePositions[i].x = 0;
        characterPortraitSpriteSheetTexturePositions[i].w = 64;
        characterPortraitSpriteSheetTexturePositions[i].h = 64;
        partyCharacterPortraitSpriteSheetTexturePositions[i].x = MAXIMUM_SCREEN_WIDTH / 2;
        partyCharacterPortraitSpriteSheetTexturePositions[i].w = 64;
        partyCharacterPortraitSpriteSheetTexturePositions[i].h = 64;
        prenom[i] = team[i]->getFirstName();
        hitPoints[i] = team[i]->getHitPoints();
        magicPoints[i] = team[i]->getMagicPoints();
        maximumHitPoints[i] = team[i]->getMaximumHitPoints();
        maximumMagicPoints[i] = team[i]->getMaximumMagicPoints();
        levels[i] = team[i]->getLevel();
        sprintf(maximumHitPointValueArray, "HP : %d / %d", hitPoints[i], maximumHitPoints[i]);
        sprintf(maximumMagicPointValueArray, "MP : %d / %d", magicPoints[i], maximumMagicPoints[i]);
        sprintf(levelArray, "Level : %d", levels[i]);
        firstNameStatisticTextTexturePosition[i].x = 70;
        firstNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, prenom[i].c_str(), fontColor));
        TTF_SizeText(secondaryArialFont, prenom[i].c_str(), &statTextWidth, &statTextHeight);
        firstNameStatisticTextTexturePosition[i].w = statTextWidth;
        firstNameStatisticTextTexturePosition[i].h = statTextHeight;
        levelStatisticTextTexturePosition[i].x = 70;
        levelStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, levelArray, fontColor));
        TTF_SizeText(secondaryArialFont, levelArray, &statTextWidth, &statTextHeight);
        levelStatisticTextTexturePosition[i].w = statTextWidth;
        levelStatisticTextTexturePosition[i].h = statTextHeight;
        hitPointsStatiticPositions[i].x = 70;
        hitPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, maximumHitPointValueArray, fontColor));
        TTF_SizeText(secondaryArialFont, maximumHitPointValueArray, &statTextWidth, &statTextHeight);
        hitPointsStatiticPositions[i].w = statTextWidth;
        hitPointsStatiticPositions[i].h = statTextHeight;
        magicPointsStatiticPositions[i].x = 70;
        magicPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, maximumMagicPointValueArray, fontColor));
        TTF_SizeText(secondaryArialFont, maximumMagicPointValueArray, &statTextWidth, &statTextHeight);
        magicPointsStatiticPositions[i].w = statTextWidth;
        magicPointsStatiticPositions[i].h = statTextHeight;

        if (i == FIRST_TEAM_MEMBER)
        {
            characterPortraitSpriteSheetTexturePositions[i].y = 45;
            partyCharacterPortraitSpriteSheetTexturePositions[i].y = 195;
            firstNameStatisticTextTexturePosition[i].y = 45;
            levelStatisticTextTexturePosition[i].y = 70;
            hitPointsStatiticPositions[i].y = 95;
            magicPointsStatiticPositions[i].y = 120;
        }
        else if (i == SECOND_TEAM_MEMBER)
        {
            characterPortraitSpriteSheetTexturePositions[i].y = 150;
            partyCharacterPortraitSpriteSheetTexturePositions[i].y = 245;
            firstNameStatisticTextTexturePosition[i].y = 150;
            levelStatisticTextTexturePosition[i].y = 175;
            hitPointsStatiticPositions[i].y = 200;
            magicPointsStatiticPositions[i].y = 225;
        }
        else if (i == THIRD_TEAM_MEMBER)
        {
            characterPortraitSpriteSheetTexturePositions[i].y = 255;
            partyCharacterPortraitSpriteSheetTexturePositions[i].y = 300;
            firstNameStatisticTextTexturePosition[i].y = 255;
            levelStatisticTextTexturePosition[i].y = 280;
            hitPointsStatiticPositions[i].y = 305;
            magicPointsStatiticPositions[i].y = 330;
        }
        else if (i == FOURTH_TEAM_MEMBER)
        {
            characterPortraitSpriteSheetTexturePositions[i].y = 360;
            partyCharacterPortraitSpriteSheetTexturePositions[i].y = 350;
            firstNameStatisticTextTexturePosition[i].y = 360;
            levelStatisticTextTexturePosition[i].y = 385;
            hitPointsStatiticPositions[i].y = 410;
            magicPointsStatiticPositions[i].y = 435;
        }
    }

    linePosition.x = MAXIMUM_SCREEN_WIDTH / 2;
    linePosition.y = 0;
    linePosition.w = 2;
    linePosition.h = MAXIMUM_SCREEN_HEIGHT;

    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            horizontalLinePosition[i].x = 0;
            horizontalLinePosition[i].y = 40;
            horizontalLinePosition[i].w = MAXIMUM_SCREEN_WIDTH;
            horizontalLinePosition[i].h = 2;
        }
        else
        {
            horizontalLinePosition[i].x = MAXIMUM_SCREEN_WIDTH / 2;
            horizontalLinePosition[i].y = 143;
            horizontalLinePosition[i].w = MAXIMUM_SCREEN_WIDTH / 2;
            horizontalLinePosition[i].h = 2;
        }
    }

    menuTitlePosition.x = 0;
    menuTitlePosition.y = 0;
    menuTitle = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, "Party", fontColor));
    int titreMenuWidth = 0;
    int titreMenuHeight = 0;
    TTF_SizeText(mainArialFont, "Party", &titreMenuWidth, &titreMenuHeight);
    menuTitlePosition.w = titreMenuWidth;
    menuTitlePosition.h = titreMenuHeight;

    characterPortraitSpriteSheetTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("tof.png"));

    partyCharacterPortraitSpriteSheetTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("tofGroupe.png"));

    partyCharacterPortraitClipPositions[FIRST_TEAM_MEMBER].x = 0;
    partyCharacterPortraitClipPositions[FIRST_TEAM_MEMBER].y = 0;
    partyCharacterPortraitClipPositions[FIRST_TEAM_MEMBER].w = 192 / 4;
    partyCharacterPortraitClipPositions[FIRST_TEAM_MEMBER].h = 192 / 4;

    partyCharacterPortraitClipPositions[SECOND_TEAM_MEMBER].x = 3 * 192 / 4;
    partyCharacterPortraitClipPositions[SECOND_TEAM_MEMBER].y = 0;
    partyCharacterPortraitClipPositions[SECOND_TEAM_MEMBER].w = 192 / 4;
    partyCharacterPortraitClipPositions[SECOND_TEAM_MEMBER].h = 192 / 4;

    partyCharacterPortraitClipPositions[THIRD_TEAM_MEMBER].x = 2 * 192 / 4;
    partyCharacterPortraitClipPositions[THIRD_TEAM_MEMBER].y = 0;
    partyCharacterPortraitClipPositions[THIRD_TEAM_MEMBER].w = 192 / 4;
    partyCharacterPortraitClipPositions[THIRD_TEAM_MEMBER].h = 192 / 4;

    partyCharacterPortraitClipPositions[FOURTH_TEAM_MEMBER].x = 1 * 192 / 4;
    partyCharacterPortraitClipPositions[FOURTH_TEAM_MEMBER].y = 0;
    partyCharacterPortraitClipPositions[FOURTH_TEAM_MEMBER].w = 192 / 4;
    partyCharacterPortraitClipPositions[FOURTH_TEAM_MEMBER].h = 192 / 4;

    characterPortraitClipPositions[FIRST_TEAM_MEMBER].x = 0;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].h = 192 / 4;

    characterPortraitClipPositions[SECOND_TEAM_MEMBER].x = 3 * 192 / 4;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].h = 192 / 4;

    characterPortraitClipPositions[THIRD_TEAM_MEMBER].x = 2 * 192 / 4;
    characterPortraitClipPositions[THIRD_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[THIRD_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[THIRD_TEAM_MEMBER].h = 192 / 4;

    characterPortraitClipPositions[FOURTH_TEAM_MEMBER].x = 1 * 192 / 4;
    characterPortraitClipPositions[FOURTH_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[FOURTH_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[FOURTH_TEAM_MEMBER].h = 192 / 4;

    if (!characterPortraitSpriteSheetTexture)
    {
        fprintf(stderr, "An error occured during the tof.png spritesheet loading for the following reason : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (!partyCharacterPortraitSpriteSheetTexture)
    {
        fprintf(stderr, "An error occured during the tofGroupe.png spritesheet loading for the following reason : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

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
            case SDLK_ESCAPE:

                isWaitingInputs = false;
                this->playCancelSound();

                break;

            case SDLK_SPACE:
                break;

            case SDLK_RETURN:

                break;

            case SDLK_UP:

                if (curssorPosition.y == characterPortraitSpriteSheetTexturePositions[teamSize - 1].y)
                {
                    memberIndex = teamSize - 1;
                    curssorPosition.y = characterPortraitSpriteSheetTexturePositions[--memberIndex].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == characterPortraitSpriteSheetTexturePositions[FIRST_TEAM_MEMBER].y)
                {
                    curssorPosition.y = characterPortraitSpriteSheetTexturePositions[teamSize - 1].y;
                    memberIndex = teamSize - 1;
                    this->playMovementSound();
                }
                else
                {
                    curssorPosition.y = characterPortraitSpriteSheetTexturePositions[--memberIndex].y;
                    this->playMovementSound();
                }
                break;

            case SDLK_DOWN:

                if (curssorPosition.y == characterPortraitSpriteSheetTexturePositions[teamSize - 1].y)
                {
                    memberIndex = FIRST_TEAM_MEMBER;
                    curssorPosition.y = characterPortraitSpriteSheetTexturePositions[memberIndex].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == characterPortraitSpriteSheetTexturePositions[FIRST_TEAM_MEMBER].y)
                {
                    curssorPosition.y = characterPortraitSpriteSheetTexturePositions[++memberIndex].y;
                    this->playMovementSound();
                }
                else
                {
                    curssorPosition.y = characterPortraitSpriteSheetTexturePositions[++memberIndex].y;
                    this->playMovementSound();
                }
                break;

            case SDLK_RIGHT:

                break;

            default:
                cout << "ok" << endl;
                break;
            }
            break;
        }

        displayMenuElements(team, renderer);
    }
}

void PartyMenu::displayMenuElements(std::vector<Character *> team, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, &menuPosition);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 36, 70);
    SDL_RenderFillRect(renderer, &curssorPosition);

    for (int i = 0; i < team.size(); i++)
    {
        SDL_RenderCopy(renderer, characterPortraitSpriteSheetTexture, &characterPortraitClipPositions[i], &characterPortraitSpriteSheetTexturePositions[i]);
        SDL_RenderCopy(renderer, partyCharacterPortraitSpriteSheetTexture, &partyCharacterPortraitClipPositions[i], &partyCharacterPortraitSpriteSheetTexturePositions[i]);
        SDL_RenderCopy(renderer, firstNameStatisticTextTexture[i], NULL, &firstNameStatisticTextTexturePosition[i]);
        SDL_RenderCopy(renderer, levelStatisticTextTexture[i], NULL, &levelStatisticTextTexturePosition[i]);
        SDL_RenderCopy(renderer, hitPointsStatisticTextTexture[i], NULL, &hitPointsStatiticPositions[i]);
        SDL_RenderCopy(renderer, magicPointsStatisticTextTexture[i], NULL, &magicPointsStatiticPositions[i]);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &linePosition);

    for (int i = 0; i < 2; i++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &horizontalLinePosition[i]);
    }

    SDL_RenderCopy(renderer, menuTitle, NULL, &menuTitlePosition);

    SDL_RenderPresent(renderer);
}
