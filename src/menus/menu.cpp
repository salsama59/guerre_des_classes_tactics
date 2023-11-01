#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ft2build.h>
#include "menu.h"
#include "../game/game.h"
#include "../dataObjects/character.h"
#include "statusMenu.h"
#include "partyMenu.h"
#include "equipmentMenu.h"
#include "../enums/teamMemberSlotsEnum.h"
#include "../enums/equipmentActionsEnum.h"
#include "../enums/armorTypesEnum.h"
#include "../enums/menuOptionsEnum.h"
#include "inventoryMenu.h"
#include "../dataObjects/inventoryBundle.h"
#include "../dataObjects/sceneInputData.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Menu::Menu(Game &game)
{
    renderer = game.getRenderer();
    menuPosition.x = 0;
    menuPosition.y = 0;
    menuTexture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    MAXIMUM_SCREEN_WIDTH, MAXIMUM_SCREEN_HEIGHT);

    SDL_AudioSpec audioSpec;
    audioSpec.freq = MIX_DEFAULT_FREQUENCY;
    audioSpec.format = MIX_DEFAULT_FORMAT;
    audioSpec.channels = MIX_DEFAULT_CHANNELS;
    int channelNumber = 4;
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 15) < 0)
    {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        exit(2);
    }
    else
    {
        Mix_QuerySpec(&audioSpec.freq, &audioSpec.format, &channelNumber);
        SDL_Log("Opened audio at %d Hz %d bit%s %s audio buffer\n", audioSpec.freq,
                (audioSpec.format & 0xFF),
                (SDL_AUDIO_ISFLOAT(audioSpec.format) ? " (float)" : ""),
                (audioSpec.channels > 2) ? "surround" : (audioSpec.channels > 1) ? "stereo"
                                                                                 : "mono");
    }

    /* Set the music volume */
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    moveSound = Mix_LoadWAV("assets/sounds/deplacement.mp3");

    if (moveSound == NULL)
    {
        SDL_Log("Couldn't open audio file %s : %s\n", "assets/sounds/deplacement.mp3", SDL_GetError());
        exit(2);
    }

    validationSound = Mix_LoadWAV("assets/sounds/validation.wav");

    if (validationSound == NULL)
    {
        SDL_Log("Couldn't open audio file %s : %s\n", "assets/sounds/validation.wav", SDL_GetError());
        exit(2);
    }

    cancelationSound = Mix_LoadWAV("assets/sounds/annulation.wav");

    if (cancelationSound == NULL)
    {
        SDL_Log("Couldn't open audio file %s : %s\n", "assets/sounds/annulation.wav", SDL_GetError());
        exit(2);
    }

    menuOpeningSound = Mix_LoadWAV("assets/sounds/Menu.mp3");

    if (menuOpeningSound == NULL)
    {
        SDL_Log("Couldn't open audio file %s : %s\n", "assets/sounds/Menu.mp3", SDL_GetError());
        exit(2);
    }
}

Menu::Menu()
{
}

Menu::~Menu()
{
    Mix_CloseAudio();
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(validationSound);
    Mix_FreeChunk(cancelationSound);
    Mix_FreeChunk(menuOpeningSound);
}

void Menu::playMovementSound()
{
    SDL_Log("Playing %s\n", "assets/sounds/deplacement.mp3");
    Mix_PlayChannel(0, moveSound, 0);
}

void Menu::playValidationSound()
{
    SDL_Log("Playing %s\n", "assets/sounds/validation.wav");
    Mix_PlayChannel(0, validationSound, 0);
}

void Menu::playCancelSound()
{
    SDL_Log("Playing %s\n", "assets/sounds/annulation.wav");
    Mix_PlayChannel(0, cancelationSound, 0);
}

void Menu::playMainMenuOpeningSound()
{
    SDL_Log("Playing %s\n", "assets/sounds/Menu.mp3");
    Mix_PlayChannel(0, menuOpeningSound, 0);
}

void Menu::displayMainMenu(std::vector<Character *> team, std::vector<Character *> party, SDL_Renderer *renderer, std::vector<Weapon *> weaponsInventory, std::vector<Helmet *> helmetsInventory, std::vector<BodyArmor *> armorsInventory, std::vector<Shield *> shieldInventory, std::vector<Boots *> bootsInventory, Game *game)
{

    vector<Resource *> resources;
    Resource *resource = new Resource("test", "assets/spriteSheets/tof.png", ResourceTypeEnum::IMAGE);
    resources.push_back(resource);
    StatusMenu *statusMenu = new StatusMenu(renderer);
    EquipmentMenu *equipmentMenu = new EquipmentMenu(renderer);
    PartyMenu *partyMenu = new PartyMenu(renderer);
    InventoryMenu *inventoryMenu = new InventoryMenu(resources, renderer);

    bool isWaitingInputs = true;
    int trueTypeFontInitializationResult = 0, menuCurssorIndex = 0, teamSize = 0;

    teamSize = team.size();
    int hitPoints[teamSize], magicPoints[teamSize], experiencePoints[teamSize], nextLevelExperiencePoints[teamSize], maximumHitPoints[teamSize], maximumMagicPoints[teamSize], levels[teamSize];
    std::string firstName[teamSize];

    trueTypeFontInitializationResult = TTF_Init();

    if (trueTypeFontInitializationResult == -1)
    {
        fprintf(stderr, "An error occured during SDL_TTF initialization for the following reason : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }

    const char *menuItemArray[9] = {"Inventory", "Equipments", "Status", "Party", "Abilities", "Save", "Load", "Options", "Exit"};
    vector<string> menuItems(9);

    mainArialFont = TTF_OpenFont("assets/fonts/arial.ttf", 30);
    secondaryArialFont = TTF_OpenFont("assets/fonts/arial.ttf", 15);
    fontColor = {255, 255, 255};

    TTF_SetFontStyle(secondaryArialFont, TTF_STYLE_BOLD);

    for (int i = 0; i < menuItems.size(); i++)
    {
        menuItems[i] = menuItemArray[i];
        menuItemTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, menuItems[i].c_str(), fontColor));
        int mainMenuItemWidth = 0;
        int mainMenuItemHeight = 0;
        TTF_SizeText(mainArialFont, menuItems[i].c_str(), &mainMenuItemWidth, &mainMenuItemHeight);
        menuItemTextTexturePosition[i].x = 0;
        menuItemTextTexturePosition[i].y = i * 50;
        menuItemTextTexturePosition[i].w = mainMenuItemWidth;
        menuItemTextTexturePosition[i].h = mainMenuItemHeight;
    }

    for (int i = 0; i < teamSize; i++)
    {
        int partyStatisticTextWidth = 0;
        int partyStatisticTextHeight = 0;

        levels[i] = team[i]->getLevel();
        firstName[i] = team[i]->getFirstName();
        hitPoints[i] = team[i]->getHitPoints();
        magicPoints[i] = team[i]->getMagicPoints();
        maximumHitPoints[i] = team[i]->getMaximumHitPoints();
        maximumMagicPoints[i] = team[i]->getMaximumMagicPoints();
        experiencePoints[i] = team[i]->getExperience();
        nextLevelExperiencePoints[i] = team[i]->getNextLevelExperiencePoints();
        sprintf(maximumHitPointValueArray, "HP : %d / %d", hitPoints[i], maximumHitPoints[i]);
        sprintf(maximumMagicPointValueArray, "MP : %d / %d", magicPoints[i], maximumMagicPoints[i]);
        sprintf(experienceArray, "Experience %d / %d", experiencePoints[i], nextLevelExperiencePoints[i]);
        sprintf(levelArray, "Level : %d", levels[i]);
        firstNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, firstName[i].c_str(), fontColor));
        TTF_SizeText(secondaryArialFont, firstName[i].c_str(), &partyStatisticTextWidth, &partyStatisticTextHeight);
        firstNameStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH / 2) + 90;
        firstNameStatisticTextTexturePosition[i].h = partyStatisticTextHeight;
        firstNameStatisticTextTexturePosition[i].w = partyStatisticTextWidth;
        levelStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, levelArray, fontColor));
        TTF_SizeText(secondaryArialFont, levelArray, &partyStatisticTextWidth, &partyStatisticTextHeight);
        levelStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH / 2) + 90;
        levelStatisticTextTexturePosition[i].h = partyStatisticTextHeight;
        levelStatisticTextTexturePosition[i].w = partyStatisticTextWidth;
        hitPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, maximumHitPointValueArray, fontColor));
        TTF_SizeText(secondaryArialFont, maximumHitPointValueArray, &partyStatisticTextWidth, &partyStatisticTextHeight);
        hitPointsStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH / 2) + 90;
        hitPointsStatisticTextTexturePosition[i].h = partyStatisticTextHeight;
        hitPointsStatisticTextTexturePosition[i].w = partyStatisticTextWidth;
        magicPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, maximumMagicPointValueArray, fontColor));
        TTF_SizeText(secondaryArialFont, maximumMagicPointValueArray, &partyStatisticTextWidth, &partyStatisticTextHeight);
        magicPointsStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH / 2) + 90;
        magicPointsStatisticTextTexturePosition[i].h = partyStatisticTextHeight;
        magicPointsStatisticTextTexturePosition[i].w = partyStatisticTextWidth;
        experienceStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(secondaryArialFont, experienceArray, fontColor));
        TTF_SizeText(secondaryArialFont, experienceArray, &partyStatisticTextWidth, &partyStatisticTextHeight);
        experienceStatisticTextTextureposition[i].x = (MAXIMUM_SCREEN_WIDTH / 2) + 90;
        experienceStatisticTextTextureposition[i].h = partyStatisticTextHeight;
        experienceStatisticTextTextureposition[i].w = partyStatisticTextWidth;

        firstNameStatisticTextTexturePosition[i].y = 10 + i * 120;
        levelStatisticTextTexturePosition[i].y = 30 + i * 120;
        hitPointsStatisticTextTexturePosition[i].y = 50 + i * 120;
        magicPointsStatisticTextTexturePosition[i].y = 70 + i * 120;
        experienceStatisticTextTextureposition[i].y = 90 + i * 120;
    }

    curssorPosition.w = 185;
    curssorPosition.h = 35;
    curssorPosition.x = 0;
    curssorPosition.y = 0;

    linePosition.x = MAXIMUM_SCREEN_WIDTH / 2;
    linePosition.y = 0;
    linePosition.w = 2;
    linePosition.h = MAXIMUM_SCREEN_HEIGHT;

    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            continue;
        }

        horizontalLinePosition[i].x = MAXIMUM_SCREEN_WIDTH / 2;
        horizontalLinePosition[i].y = i * (MAXIMUM_SCREEN_HEIGHT / 4);
        horizontalLinePosition[i].w = MAXIMUM_SCREEN_WIDTH / 2;
        horizontalLinePosition[i].h = 2;
    }

    characterPortraitSpriteSheetTexturePositions[FIRST_TEAM_MEMBER].x = (MAXIMUM_SCREEN_WIDTH / 2) + 12;
    characterPortraitSpriteSheetTexturePositions[FIRST_TEAM_MEMBER].y = 30;
    characterPortraitSpriteSheetTexturePositions[FIRST_TEAM_MEMBER].w = 64;
    characterPortraitSpriteSheetTexturePositions[FIRST_TEAM_MEMBER].h = 64;
    characterPortraitSpriteSheetTexturePositions[SECOND_TEAM_MEMBER].x = (MAXIMUM_SCREEN_WIDTH / 2) + 12;
    characterPortraitSpriteSheetTexturePositions[SECOND_TEAM_MEMBER].y = 150;
    characterPortraitSpriteSheetTexturePositions[SECOND_TEAM_MEMBER].w = 64;
    characterPortraitSpriteSheetTexturePositions[SECOND_TEAM_MEMBER].h = 64;
    characterPortraitSpriteSheetTexturePositions[THIRD_TEAM_MEMBER].x = (MAXIMUM_SCREEN_WIDTH / 2) + 12;
    characterPortraitSpriteSheetTexturePositions[THIRD_TEAM_MEMBER].y = 270;
    characterPortraitSpriteSheetTexturePositions[THIRD_TEAM_MEMBER].w = 64;
    characterPortraitSpriteSheetTexturePositions[THIRD_TEAM_MEMBER].h = 64;
    characterPortraitSpriteSheetTexturePositions[FOURTH_TEAM_MEMBER].x = (MAXIMUM_SCREEN_WIDTH / 2) + 12;
    characterPortraitSpriteSheetTexturePositions[FOURTH_TEAM_MEMBER].y = 390;
    characterPortraitSpriteSheetTexturePositions[FOURTH_TEAM_MEMBER].w = 64;
    characterPortraitSpriteSheetTexturePositions[FOURTH_TEAM_MEMBER].h = 64;
    characterPortraitSpriteSheetTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/spriteSheets/tof.png"));

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

    if (characterPortraitSpriteSheetTexture == NULL)
    {
        fprintf(stderr, "An error occured during the tof.png spritesheet loading for the following reason : %s\n", SDL_GetError());
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

            case SDLK_RETURN:

                if (curssorPosition.y == menuItemTextTexturePosition[INVENTORY].y)
                {
                    this->playValidationSound();
                    InventoryBundle *inventoryBundle = new InventoryBundle(weaponsInventory, helmetsInventory, armorsInventory, shieldInventory, bootsInventory);
                    SceneInputData *sceneInputData = new SceneInputData(party, team, inventoryBundle);
                    inventoryMenu->executeScene(sceneInputData);
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[EQUIPEMENTS].y)
                {
                    this->playValidationSound();
                    equipmentMenu->displayEquipmentMenu(team, renderer, weaponsInventory, helmetsInventory, armorsInventory, shieldInventory, bootsInventory, game);
                    weaponsInventory = game->getWeaponsInventory();
                    helmetsInventory = game->getHelmetsInventory();
                    armorsInventory = game->getArmorsInevtory();
                    shieldInventory = game->getShieldsInventory();
                    bootsInventory = game->getBootsInventory();
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[STATUS].y)
                {
                    this->playValidationSound();
                    statusMenu->displayStatusMenu(team, renderer);
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[PARTY].y)
                {
                    this->playValidationSound();
                    partyMenu->displayPartyMenu(party, team, renderer, game);
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[ABILITIES].y)
                {
                    this->playValidationSound();
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[SAVE].y)
                {
                    this->playValidationSound();
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[LOAD].y)
                {
                    this->playValidationSound();
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[OPTIONS].y)
                {
                    this->playValidationSound();
                }
                else if (curssorPosition.y == menuItemTextTexturePosition[EXIT].y)
                {
                    this->playValidationSound();
                    isWaitingInputs = false;
                }
                break;

            case SDLK_UP:
                if (curssorPosition.y == menuItemTextTexturePosition[INVENTORY].y)
                {
                    curssorPosition.y = menuItemTextTexturePosition[EXIT].y;
                    menuCurssorIndex = EXIT;
                }
                else
                {
                    curssorPosition.y = menuItemTextTexturePosition[--menuCurssorIndex].y;
                }
                this->playMovementSound();
                break;

            case SDLK_DOWN:
                if (curssorPosition.y == menuItemTextTexturePosition[EXIT].y)
                {
                    curssorPosition.y = menuItemTextTexturePosition[INVENTORY].y;
                    menuCurssorIndex = INVENTORY;
                }
                else
                {
                    curssorPosition.y = menuItemTextTexturePosition[++menuCurssorIndex].y;
                }
                this->playMovementSound();
                break;
            }
            break;
        }

        this->displayMenuElements(menuItems, team);
    }
}

void Menu::displayMenuElements(std::vector<std::string> menuItems, std::vector<Character *> team)
{
    int menuElementsSize = menuItems.size();
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, menuTexture, NULL, &menuPosition);

    for (int i = 0; i < menuElementsSize; i++)
    {
        SDL_RenderCopy(renderer, menuItemTextTexture[i], NULL, &menuItemTextTexturePosition[i]);
    }

    for (int i = 0; i < team.size(); i++)
    {
        SDL_RenderCopy(renderer, characterPortraitSpriteSheetTexture, &characterPortraitClipPositions[i], &characterPortraitSpriteSheetTexturePositions[i]);
        SDL_RenderCopy(renderer, firstNameStatisticTextTexture[i], NULL, &firstNameStatisticTextTexturePosition[i]);
        SDL_RenderCopy(renderer, levelStatisticTextTexture[i], NULL, &levelStatisticTextTexturePosition[i]);
        SDL_RenderCopy(renderer, hitPointsStatisticTextTexture[i], NULL, &hitPointsStatisticTextTexturePosition[i]);
        SDL_RenderCopy(renderer, magicPointsStatisticTextTexture[i], NULL, &magicPointsStatisticTextTexturePosition[i]);
        SDL_RenderCopy(renderer, experienceStatisticTextTexture[i], NULL, &experienceStatisticTextTextureposition[i]);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 36, 70);
    SDL_RenderFillRect(renderer, &curssorPosition);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 178);
    SDL_RenderFillRect(renderer, &linePosition);

    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 178);
        SDL_RenderFillRect(renderer, &horizontalLinePosition[i]);
    }

    SDL_RenderPresent(renderer);
}
