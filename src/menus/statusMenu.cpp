#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../src/menus/statusMenu.h"
#include "../src/dataObjects/weapon.h"
#include "../src/menus/menu.h"
#include "../src/dataObjects/character.h"
#include "../src/dataObjects/equipment.h"
#include "../enums/teamMemberSlotsEnum.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

StatusMenu::StatusMenu(SDL_Renderer *renderer) : Menu()
{
    menuTexture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    MAXIMUM_SCREEN_WIDTH, MAXIMUM_SCREEN_HEIGHT);
    menuPosition.x = 0;
    menuPosition.y = 0;

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

void StatusMenu::displayStatusMenu(std::vector<Character *> team, SDL_Renderer *renderer)
{
    bool isWaitingInputs = true;
    int trueTypeFontInitializationResult = 0, teamSize = 0, memberIndex = 0;
    teamSize = team.size();
    float dodgeRate[teamSize], accuracy[teamSize];
    int hitPoints[teamSize], magicPoints[teamSize], experiences[teamSize], nextLevelExperience[teamSize], maximumHitpoints[teamSize], maximumMagicPoints[teamSize], levels[teamSize], strenghts[teamSize], defences[teamSize], magics[teamSize], willPowers[teamSize], speeds[teamSize], lucks[teamSize];
    string surnames[teamSize], firstNames[teamSize], weaponNames[teamSize], armorNames[4];
    std::vector<Equipment> equipments;
    std::vector<Weapon> weapons;
    trueTypeFontInitializationResult = TTF_Init();
    if (trueTypeFontInitializationResult == -1)
    {
        fprintf(stderr, "An error occured during SDL_TTF initialization for the following reason : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }
    mainArialFont = TTF_OpenFont("assets/fonts/arial.ttf", 25);
    fontColor = {255, 255, 255};
    for (int i = 0; i < teamSize; i++)
    {
        levels[i] = team[i]->getLevel();
        firstNames[i] = team[i]->getFirstName();
        hitPoints[i] = team[i]->getHitPoints();
        magicPoints[i] = team[i]->getMagicPoints();
        maximumHitpoints[i] = team[i]->getMaximumHitPoints();
        maximumMagicPoints[i] = team[i]->getMaximumMagicPoints();
        experiences[i] = team[i]->getExperience();
        nextLevelExperience[i] = team[i]->getNextLevelExperiencePoints();
        strenghts[i] = team[i]->getStrenght();
        defences[i] = team[i]->getDefence();
        magics[i] = team[i]->getMagic();
        willPowers[i] = team[i]->getWillPower();
        speeds[i] = team[i]->getSpeed();
        dodgeRate[i] = team[i]->getDodgeRate();
        accuracy[i] = team[i]->getAccuracy();
        lucks[i] = team[i]->getLuck();
        surnames[i] = team[i]->getSurname();
        weapons.push_back(team[i]->getEquipedWeapon());
        equipments = team[i]->getEquipedEquipments();
        for (int j = 0; j < equipments.size(); j++)
        {
            armorNames[j] = equipments[j].GetName();
            armorNameTextTexturePosition[j].x = 450;
            if (j == 0)
            {
                armorNameTextTexturePosition[j].y = 130;
            }
            else if (j > 0)
            {
                armorNameTextTexturePosition[j].y = armorNameTextTexturePosition[j - 1].y + 30;
            }

            int armorNameTextTextureWidth = 0;
            int armorNameTextTextureHeight = 0;
            TTF_SizeText(mainArialFont, armorNames[j].c_str(), &armorNameTextTextureWidth, &armorNameTextTextureHeight);
            armorNameTextTexturePosition[j].w = armorNameTextTextureWidth;
            armorNameTextTexturePosition[j].h = armorNameTextTextureHeight;

            if (i == FIRST_TEAM_MEMBER)
            {
                memberOneArmorNameTextTexture[j] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, armorNames[j].c_str(), fontColor));
            }

            if (i == SECOND_TEAM_MEMBER)
            {
                memberTwoArmorNameTextTexture[j] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, armorNames[j].c_str(), fontColor));
            }
        }
        weaponNames[i] = weapons[i].GetName();
        sprintf(maximumHitPointValueArray, "HP : %d / %d", hitPoints[i], maximumHitpoints[i]);
        sprintf(maximumMagicPointValueArray, "MP : %d / %d", magicPoints[i], maximumMagicPoints[i]);
        sprintf(experienceArray, "Experience %d / %d", experiences[i], nextLevelExperience[i]);
        sprintf(levelArray, "Level : %d", levels[i]);
        sprintf(strenghtValueArray, "Strength : %d", strenghts[i]);
        sprintf(magicValueArray, "Magic : %d", magics[i]);
        sprintf(defenceValueArray, "Defence : %d", defences[i]);
        sprintf(willValueArray, "Will : %d", willPowers[i]);
        sprintf(speedValueArray, "Speed : %d", speeds[i]);
        sprintf(dodgeRateValueArray, "Dodge rate : %.2f %", dodgeRate[i]);
        sprintf(accuracyValueArray, "Accuracy : %.2f %", accuracy[i]);
        sprintf(luckValueArray, "Luck : %d", lucks[i]);

        nameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, surnames[i].c_str(), fontColor));
        int lastNamStatisticTextTextureWidth = 0;
        int lastNamStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, surnames[i].c_str(), &lastNamStatisticTextTextureWidth, &lastNamStatisticTextTextureHeight);
        lastNamStatisticTextTexturePosition[i].w = lastNamStatisticTextTextureWidth;
        lastNamStatisticTextTexturePosition[i].h = lastNamStatisticTextTextureHeight;
        lastNamStatisticTextTexturePosition[i].x = 450;
        lastNamStatisticTextTexturePosition[i].y = 20;

        firstNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, firstNames[i].c_str(), fontColor));
        int firstNameStatisticTextTextureWidth = 0;
        int firstNameStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, firstNames[i].c_str(), &firstNameStatisticTextTextureWidth, &firstNameStatisticTextTextureHeight);
        firstNameStatisticTextTexturePosition[i].w = firstNameStatisticTextTextureWidth;
        firstNameStatisticTextTexturePosition[i].h = firstNameStatisticTextTextureHeight;
        firstNameStatisticTextTexturePosition[i].x = 450;
        firstNameStatisticTextTexturePosition[i].y = 40;

        levelStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, levelArray, fontColor));
        int levelTextTextureWidth = 0;
        int levelTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, levelArray, &levelTextTextureWidth, &levelTextTextureHeight);
        levelTextTexturePosition[i].w = levelTextTextureWidth;
        levelTextTexturePosition[i].h = levelTextTextureHeight;
        levelTextTexturePosition[i].x = 450;
        levelTextTexturePosition[i].y = 60;

        hitPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, maximumHitPointValueArray, fontColor));
        int hitPointsTextTextureWidth = 0;
        int hitPointsTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, maximumHitPointValueArray, &hitPointsTextTextureWidth, &hitPointsTextTextureHeight);
        hitPointsTextTexturePosition[i].w = hitPointsTextTextureWidth;
        hitPointsTextTexturePosition[i].h = hitPointsTextTextureHeight;
        hitPointsTextTexturePosition[i].x = 0;
        hitPointsTextTexturePosition[i].y = 0;

        magicPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, maximumMagicPointValueArray, fontColor));
        int magicPointsTextTextureWidth = 0;
        int magicPointsTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, maximumMagicPointValueArray, &magicPointsTextTextureWidth, &magicPointsTextTextureHeight);
        magicPointsTextTexturePosition[i].w = magicPointsTextTextureWidth;
        magicPointsTextTexturePosition[i].h = magicPointsTextTextureHeight;
        magicPointsTextTexturePosition[i].x = 0;
        magicPointsTextTexturePosition[i].y = MAXIMUM_SCREEN_HEIGHT / 11;

        experienceStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, experienceArray, fontColor));
        int experiencePointsTextTextureWidth = 0;
        int experiencePointsTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, experienceArray, &experiencePointsTextTextureWidth, &experiencePointsTextTextureHeight);
        experiencePointsTextTexturePosition[i].w = experiencePointsTextTextureWidth;
        experiencePointsTextTexturePosition[i].h = experiencePointsTextTextureHeight;
        experiencePointsTextTexturePosition[i].x = 0;
        experiencePointsTextTexturePosition[i].y = 2 * MAXIMUM_SCREEN_HEIGHT / 11;

        strenghtStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, strenghtValueArray, fontColor));
        int strenghtStatisticTextTextureWidth = 0;
        int strenghtStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, strenghtValueArray, &strenghtStatisticTextTextureWidth, &strenghtStatisticTextTextureHeight);
        strenghtStatisticTextTexturePosition[i].w = strenghtStatisticTextTextureWidth;
        strenghtStatisticTextTexturePosition[i].h = strenghtStatisticTextTextureHeight;
        strenghtStatisticTextTexturePosition[i].x = 0;
        strenghtStatisticTextTexturePosition[i].y = 3 * MAXIMUM_SCREEN_HEIGHT / 11;

        defenceStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, defenceValueArray, fontColor));
        int defenceStatisticTextTextureWidth = 0;
        int defenceStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, defenceValueArray, &defenceStatisticTextTextureWidth, &defenceStatisticTextTextureHeight);
        defenceStatisticTextTexturePosition[i].w = defenceStatisticTextTextureWidth;
        defenceStatisticTextTexturePosition[i].h = defenceStatisticTextTextureHeight;
        defenceStatisticTextTexturePosition[i].x = 0;
        defenceStatisticTextTexturePosition[i].y = 4 * MAXIMUM_SCREEN_HEIGHT / 11;

        magicStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, magicValueArray, fontColor));
        int magicStatisticTextTextureWidth = 0;
        int magicStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, magicValueArray, &magicStatisticTextTextureWidth, &magicStatisticTextTextureHeight);
        magicStatisticTextTexturePosition[i].w = magicStatisticTextTextureWidth;
        magicStatisticTextTexturePosition[i].h = magicStatisticTextTextureHeight;
        magicStatisticTextTexturePosition[i].x = 0;
        magicStatisticTextTexturePosition[i].y = 5 * MAXIMUM_SCREEN_HEIGHT / 11;

        willStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, willValueArray, fontColor));
        int willStatisticTextTextureWidth = 0;
        int willStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, willValueArray, &willStatisticTextTextureWidth, &willStatisticTextTextureHeight);
        willStatisticTextTexturePosition[i].w = willStatisticTextTextureWidth;
        willStatisticTextTexturePosition[i].h = willStatisticTextTextureHeight;
        willStatisticTextTexturePosition[i].x = 0;
        willStatisticTextTexturePosition[i].y = 6 * MAXIMUM_SCREEN_HEIGHT / 11;

        speedStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, speedValueArray, fontColor));
        int speedStatisticTextTextureWidth = 0;
        int speedStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, speedValueArray, &speedStatisticTextTextureWidth, &speedStatisticTextTextureHeight);
        speedStatisticTextTexturePosition[i].w = speedStatisticTextTextureWidth;
        speedStatisticTextTexturePosition[i].h = speedStatisticTextTextureHeight;
        speedStatisticTextTexturePosition[i].x = 0;
        speedStatisticTextTexturePosition[i].y = 7 * MAXIMUM_SCREEN_HEIGHT / 11;

        accuracyStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, accuracyValueArray, fontColor));
        int accuracyStatisticTextTextureWidth = 0;
        int accuracyStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, accuracyValueArray, &accuracyStatisticTextTextureWidth, &accuracyStatisticTextTextureHeight);
        accuracyStatisticTextTexturePosition[i].w = accuracyStatisticTextTextureWidth;
        accuracyStatisticTextTexturePosition[i].h = accuracyStatisticTextTextureHeight;
        accuracyStatisticTextTexturePosition[i].x = 0;
        accuracyStatisticTextTexturePosition[i].y = 8 * MAXIMUM_SCREEN_HEIGHT / 11;

        dodgeRateStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, dodgeRateValueArray, fontColor));
        int dodgeRateStatisticTextTextureWidth = 0;
        int dodgeRateStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, dodgeRateValueArray, &dodgeRateStatisticTextTextureWidth, &dodgeRateStatisticTextTextureHeight);
        dodgeRateStatisticTextTexturePosition[i].w = dodgeRateStatisticTextTextureWidth;
        dodgeRateStatisticTextTexturePosition[i].h = dodgeRateStatisticTextTextureHeight;
        dodgeRateStatisticTextTexturePosition[i].x = 0;
        dodgeRateStatisticTextTexturePosition[i].y = 9 * MAXIMUM_SCREEN_HEIGHT / 11;

        luckStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, luckValueArray, fontColor));
        int luckStatisticTextTextureWidth = 0;
        int luckStatisticTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, luckValueArray, &luckStatisticTextTextureWidth, &luckStatisticTextTextureHeight);
        luckStatisticTextTexturePosition[i].w = luckStatisticTextTextureWidth;
        luckStatisticTextTexturePosition[i].h = luckStatisticTextTextureHeight;
        luckStatisticTextTexturePosition[i].x = 0;
        luckStatisticTextTexturePosition[i].y = 10 * MAXIMUM_SCREEN_HEIGHT / 11;

        weaponNameTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, weaponNames[i].c_str(), fontColor));
        int weaponNameTextTextureWidth = 0;
        int weaponNameTextTextureHeight = 0;
        TTF_SizeText(mainArialFont, weaponNames[i].c_str(), &weaponNameTextTextureWidth, &weaponNameTextTextureHeight);
        weaponNameTextTexturePosition[i].w = weaponNameTextTextureWidth;
        weaponNameTextTexturePosition[i].h = weaponNameTextTextureHeight;
        weaponNameTextTexturePosition[i].x = 450;
        weaponNameTextTexturePosition[i].y = 100;
    }
    const char *equipementCategoriesTitle[5] = {"Weapon :", "Helmet :", "Armor :", "Shield :", "Boots :"};

    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            equipmentNameTextTexturesPosition[i].y = 100;
        }
        else
        {
            equipmentNameTextTexturesPosition[i].y = equipmentNameTextTexturesPosition[i - 1].y + 30;
        }

        equipmentNameTextTextures[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, equipementCategoriesTitle[i], fontColor));
        int texteEquipementWidth = 0;
        int texteEquipementHeight = 0;
        TTF_SizeText(mainArialFont, equipementCategoriesTitle[i], &texteEquipementWidth, &texteEquipementHeight);
        equipmentNameTextTexturesPosition[i].w = texteEquipementWidth;
        equipmentNameTextTexturesPosition[i].h = texteEquipementHeight;
        equipmentNameTextTexturesPosition[i].x = 325;
    }

    characterPortraitSpriteSheetTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/spriteSheets/tof.png"));
    if (characterPortraitSpriteSheetTexture == NULL)
    {
        fprintf(stderr, "An error occured during the tof.png spritesheet loading for the following reason : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE);
    }

    chararacterPortraitPosition.x = (MAXIMUM_SCREEN_WIDTH / 2);
    chararacterPortraitPosition.y = 20;
    chararacterPortraitPosition.w = 64;
    chararacterPortraitPosition.h = 64;

    characterPortraitClipPositions[FIRST_TEAM_MEMBER].x = 0;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].h = 192 / 4;

    characterPortraitClipPositions[SECOND_TEAM_MEMBER].x = 3 * 192 / 4;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].h = 192 / 4;

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

            case SDLK_UP:
                break;

            case SDLK_DOWN:
                break;

            case SDLK_RIGHT:
                if (memberIndex == (teamSize - 1))
                {
                    memberIndex = FIRST_TEAM_MEMBER;
                }
                else
                {
                    memberIndex++;
                }
                this->playMovementSound();
                break;

            case SDLK_LEFT:
                if (memberIndex == FIRST_TEAM_MEMBER)
                {
                    memberIndex = teamSize - 1;
                }
                else
                {
                    memberIndex--;
                }
                this->playMovementSound();
                break;
            }
            break;
        }

        displayMenuElements(team, memberIndex, renderer);
    }
}

void StatusMenu::displayMenuElements(std::vector<Character *> team, int memberId, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, menuTexture, NULL, &menuPosition);

    std::vector<Equipment> equipements = team[memberId]->getEquipedEquipments();

    for (int i = 0; i < equipements.size(); i++)
    {
        if (memberId == FIRST_TEAM_MEMBER)
        {
            SDL_RenderCopy(renderer, memberOneArmorNameTextTexture[i], NULL, &armorNameTextTexturePosition[i]);
        }
        if (memberId == SECOND_TEAM_MEMBER)
        {
            SDL_RenderCopy(renderer, memberTwoArmorNameTextTexture[i], NULL, &armorNameTextTexturePosition[i]);
        }
    }

    SDL_RenderCopy(renderer, nameStatisticTextTexture[memberId], NULL, &lastNamStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, firstNameStatisticTextTexture[memberId], NULL, &firstNameStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, levelStatisticTextTexture[memberId], NULL, &levelTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, hitPointsStatisticTextTexture[memberId], NULL, &hitPointsTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, magicPointsStatisticTextTexture[memberId], NULL, &magicPointsTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, experienceStatisticTextTexture[memberId], NULL, &experiencePointsTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, strenghtStatisticTextTexture[memberId], NULL, &strenghtStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, defenceStatisticTextTexture[memberId], NULL, &defenceStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, magicStatisticTextTexture[memberId], NULL, &magicStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, willStatisticTextTexture[memberId], NULL, &willStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, speedStatisticTextTexture[memberId], NULL, &speedStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, accuracyStatisticTextTexture[memberId], NULL, &accuracyStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, dodgeRateStatisticTextTexture[memberId], NULL, &dodgeRateStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, luckStatisticTextTexture[memberId], NULL, &luckStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, weaponNameTextTexture[memberId], NULL, &weaponNameTextTexturePosition[memberId]);

    for (int i = 0; i < 5; i++)
    {
        SDL_RenderCopy(renderer, equipmentNameTextTextures[i], NULL, &equipmentNameTextTexturesPosition[i]);
    }

    SDL_RenderCopy(renderer, characterPortraitSpriteSheetTexture, &characterPortraitClipPositions[memberId], &chararacterPortraitPosition);

    SDL_RenderPresent(renderer);
}
