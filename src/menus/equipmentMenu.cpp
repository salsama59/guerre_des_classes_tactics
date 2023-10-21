#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <freetype/freetype.h>
#include "equipmentMenu.h"
#include "../dataObjects/spear.h"
#include "../dataObjects/glove.h"
#include "../enums/teamMemberSlotsEnum.h"
#include "../enums/equipmentActionsEnum.h"
#include "../enums/armorTypesEnum.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

EquipmentMenu::EquipmentMenu(SDL_Renderer *ecran)
{
    menuPosition.x = 0;
    menuPosition.y = 0;
    menuTexture = SDL_CreateTexture(ecran,
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

EquipmentMenu::~EquipmentMenu()
{
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(validationSound);
    Mix_FreeChunk(cancelationSound);
}

void EquipmentMenu::displayEquipmentMenu(std::vector<Character *> team, SDL_Renderer *renderer, std::vector<Weapon *> weaponsInventory, std::vector<Helmet *> helmetsInventory, std::vector<BodyArmor *> armorsInventory, std::vector<Shield *> shieldsInventory, std::vector<Boots *> bootsInventory, Game *game)
{
    bool isWaitingInputs = true;
    int trueTypeFontInitializationResult = 0, teamMembersSize = 0, memberId = 0, weaponsInventorySize = 0, counter = 0, k = 0, l = 0, m = 0, n = 0, flag = 0, haut = 0, helmetsInventorySize = 0, armorsInventorySize = 0, shieldsInventorySize = 0, bootsInventorySize = 0;
    teamMembersSize = team.size();
    weaponsInventorySize = weaponsInventory.size();
    helmetsInventorySize = helmetsInventory.size();
    armorsInventorySize = armorsInventory.size();
    shieldsInventorySize = shieldsInventory.size();
    bootsInventorySize = bootsInventory.size();
    float dodgeRateValueArray[teamMembersSize], accuracyValueArray[teamMembersSize];
    int maximumHitPointValueArray[teamMembersSize], maximumMagicPointValueArray[teamMembersSize], strenghtValueArray[teamMembersSize], defenceValueArray[teamMembersSize], magicValueArray[teamMembersSize], willValueArray[teamMembersSize], speedValueArray[teamMembersSize], luckValueArray[teamMembersSize], damageValueArray[weaponsInventorySize];
    string membersWeaponNames[teamMembersSize], membersArmorNames[4], membersFirstNames[teamMembersSize], inventoryWeaponsNames[weaponsInventorySize], inventoryHelmetsNames[helmetsInventorySize], inventoryArmorsNames[armorsInventorySize], inventoryShieldsNames[shieldsInventorySize], inventoryBootsNames[bootsInventorySize];
    std::vector<Equipment> equipements;
    std::vector<Weapon> weapons;
    trueTypeFontInitializationResult = TTF_Init();
    if (trueTypeFontInitializationResult == -1)
    {
        fprintf(stderr, "An error occured during SDL_TTF initialization for the following reason : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }

    mainArialFont = TTF_OpenFont("assets/fonts/arial.ttf", 30);
    fontColor = {255, 255, 255};
    equipmentBonusFontColor = {255, 255, 0};

    curssorPosition.w = 105;
    curssorPosition.h = 35;
    curssorPosition.x = (MAXIMUM_SCREEN_WIDTH + 5) / 2;
    curssorPosition.y = 0;

    for (int i = 0; i < weaponsInventorySize; i++)
    {
        inventoryWeaponsNames[i] = weaponsInventory[i]->GetName();
        damageValueArray[i] = weaponsInventory[i]->getDamage();
        sprintf(this->damageValueArray, "%d", damageValueArray[i]);
        weaponNameInventoryTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryWeaponsNames[i].c_str(), fontColor));
        int texteNomArmeWidth = 0;
        int texteNomArmeHeight = 0;
        TTF_SizeText(mainArialFont, inventoryWeaponsNames[i].c_str(), &texteNomArmeWidth, &texteNomArmeHeight);
        weaponNameInventoryTextTexturePosition[i].w = texteNomArmeWidth;
        weaponNameInventoryTextTexturePosition[i].h = texteNomArmeHeight;
        weaponNameInventoryTextTexturePosition[i].x = 0;
        weaponNameInventoryTextTexturePosition[i].y = 265 + i * 30;
    }

    for (int i = 0; i < helmetsInventorySize; i++)
    {
        inventoryHelmetsNames[i] = helmetsInventory[i]->GetName();
        helmetNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryHelmetsNames[i].c_str(), fontColor));
        int texteNomArmureWidth = 0;
        int texteNomArmureHeight = 0;
        TTF_SizeText(mainArialFont, inventoryHelmetsNames[i].c_str(), &texteNomArmureWidth, &texteNomArmureHeight);
        helmetNameStatisticTextTexturePosition[i].w = texteNomArmureWidth;
        helmetNameStatisticTextTexturePosition[i].h = texteNomArmureHeight;
        helmetNameStatisticTextTexturePosition[i].x = 0;
        helmetNameStatisticTextTexturePosition[i].y = 265 + i * 30;
    }

    for (int i = 0; i < armorsInventorySize; i++)
    {
        inventoryArmorsNames[i] = armorsInventory[i]->GetName();
        armorNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryArmorsNames[i].c_str(), fontColor));
        int texteNomCuirasseWidth = 0;
        int texteNomCuirasseHeight = 0;
        TTF_SizeText(mainArialFont, inventoryArmorsNames[i].c_str(), &texteNomCuirasseWidth, &texteNomCuirasseHeight);
        armorNameStatisticTextTexturePosition[i].w = texteNomCuirasseWidth;
        armorNameStatisticTextTexturePosition[i].h = texteNomCuirasseHeight;
        armorNameStatisticTextTexturePosition[i].x = 0;
        armorNameStatisticTextTexturePosition[i].y = 265 + i * 30;
    }

    for (int i = 0; i < shieldsInventorySize; i++)
    {
        inventoryShieldsNames[i] = shieldsInventory[i]->GetName();
        shieldNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryShieldsNames[i].c_str(), fontColor));
        int texteNomBouclierWidth = 0;
        int texteNomBouclierHeight = 0;
        TTF_SizeText(mainArialFont, inventoryShieldsNames[i].c_str(), &texteNomBouclierWidth, &texteNomBouclierHeight);
        shieldNameStatisticTextTexturePosition[i].w = texteNomBouclierWidth;
        shieldNameStatisticTextTexturePosition[i].h = texteNomBouclierHeight;
        shieldNameStatisticTextTexturePosition[i].x = 0;
        shieldNameStatisticTextTexturePosition[i].y = 265 + i * 30;
    }

    for (int i = 0; i < bootsInventorySize; i++)
    {
        inventoryBootsNames[i] = bootsInventory[i]->GetName();
        bootNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryBootsNames[i].c_str(), fontColor));
        int texteNomJambiereWidth = 0;
        int texteNomJambiereHeight = 0;
        TTF_SizeText(mainArialFont, inventoryBootsNames[i].c_str(), &texteNomJambiereWidth, &texteNomJambiereHeight);
        bootNameStatisticTextTexturePosition[i].w = texteNomJambiereWidth;
        bootNameStatisticTextTexturePosition[i].h = texteNomJambiereHeight;
        bootNameStatisticTextTexturePosition[i].x = 0;
        bootNameStatisticTextTexturePosition[i].y = 265 + i * 30;
    }

    for (int i = 0; i < teamMembersSize; i++)
    {
        weapons.push_back(team[i]->getEquipedWeapon());
        membersFirstNames[i] = team[i]->getFirstName();
        equipements = team[i]->getEquipedEquipments();
        membersWeaponNames[i] = weapons[i].GetName();
        maximumHitPointValueArray[i] = team[i]->getMaximumHitPoints();
        maximumMagicPointValueArray[i] = team[i]->getMaximumMagicPoints();
        strenghtValueArray[i] = team[i]->getStrenght();
        defenceValueArray[i] = team[i]->getDefence();
        magicValueArray[i] = team[i]->getMagic();
        willValueArray[i] = team[i]->getWillPower();
        speedValueArray[i] = team[i]->getSpeed();
        dodgeRateValueArray[i] = team[i]->getDodgeRate();
        accuracyValueArray[i] = team[i]->getAccuracy();
        luckValueArray[i] = team[i]->getLuck();

        for (int j = 0; j < equipements.size(); j++)
        {
            membersArmorNames[j] = equipements[j].GetName();
            if (i == FIRST_TEAM_MEMBER)
            {
                memberOneArmorNameTextTexture[j] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, membersArmorNames[j].c_str(), fontColor));
                int texteStatNomArmureM0Width = 0;
                int texteStatNomArmureM0Height = 0;
                TTF_SizeText(mainArialFont, membersArmorNames[j].c_str(), &texteStatNomArmureM0Width, &texteStatNomArmureM0Height);
                memberGenericEquipmentNameStatisticTextTexturePosition[j].w = texteStatNomArmureM0Width;
                memberGenericEquipmentNameStatisticTextTexturePosition[j].h = texteStatNomArmureM0Height;
            }
            if (i == SECOND_TEAM_MEMBER)
            {
                memberTwoArmorNameTextTexture[j] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, membersArmorNames[j].c_str(), fontColor));
                int texteStatNomArmureM1Width = 0;
                int texteStatNomArmureM1Height = 0;
                TTF_SizeText(mainArialFont, membersArmorNames[j].c_str(), &texteStatNomArmureM1Width, &texteStatNomArmureM1Height);
                memberGenericEquipmentNameStatisticTextTexturePosition[j].w = texteStatNomArmureM1Width;
                memberGenericEquipmentNameStatisticTextTexturePosition[j].h = texteStatNomArmureM1Height;
            }
            memberGenericEquipmentNameStatisticTextTexturePosition[j].x = 150;
            memberGenericEquipmentNameStatisticTextTexturePosition[j].y = 130 + j * 30;
        }

        sprintf(this->maximumHitPointValueArray, "MAX HP : %d", maximumHitPointValueArray[i]);
        sprintf(this->maximumMagicPointValueArray, "MAX MP : %d", maximumMagicPointValueArray[i]);
        sprintf(this->strenghtValueArray, "Strenght : %d", strenghtValueArray[i]);
        sprintf(this->magicValueArray, "Magic : %d", magicValueArray[i]);
        sprintf(this->defenceValueArray, "Defence : %d", defenceValueArray[i]);
        sprintf(this->willValueArray, "Will power : %d", willValueArray[i]);
        sprintf(this->speedValueArray, "Speed : %d", speedValueArray[i]);
        sprintf(this->dodgeRateValueArray, "Dodge rate : %.2f %", dodgeRateValueArray[i]);
        sprintf(this->accuracyValueArray, "Accuracy : %.2f %", accuracyValueArray[i]);
        sprintf(this->luckValueArray, "Luck : %d", luckValueArray[i]);

        int texteStatCharacterWidth = 0;
        int texteStatCharacterHeight = 0;

        hitPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->maximumHitPointValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->maximumHitPointValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        hitPointsTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        hitPointsTextTexturePosition[i].y = 40;
        weaponHitPointsDataTextTexturePosition.x = hitPointsTextTexturePosition[i].x + 140;
        weaponHitPointsDataTextTexturePosition.y = 40;
        hitPointsTextTexturePosition[i].w = texteStatCharacterWidth;
        hitPointsTextTexturePosition[i].h = texteStatCharacterHeight;

        magicPointsStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->maximumMagicPointValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->maximumMagicPointValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        magicPointsTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        magicPointsTextTexturePosition[i].y = 2 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponMagicPointsDataTextTexturePosition.x = magicPointsTextTexturePosition[i].x + 140;
        weaponMagicPointsDataTextTexturePosition.y = 2 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        magicPointsTextTexturePosition[i].w = texteStatCharacterWidth;
        magicPointsTextTexturePosition[i].h = texteStatCharacterHeight;

        strenghtStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->strenghtValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->strenghtValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        strenghtStatisticTextTexturePositio[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        strenghtStatisticTextTexturePositio[i].y = 3 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponStrenghtDataTextTexturePosition.x = strenghtStatisticTextTexturePositio[i].x + 140;
        weaponStrenghtDataTextTexturePosition.y = 3 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        strenghtStatisticTextTexturePositio[i].w = texteStatCharacterWidth;
        strenghtStatisticTextTexturePositio[i].h = texteStatCharacterHeight;

        defenceStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->defenceValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->defenceValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        defenceStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        defenceStatisticTextTexturePosition[i].y = 4 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponDefenceDataTextTexturePosition.x = defenceStatisticTextTexturePosition[i].x + 180;
        weaponDefenceDataTextTexturePosition.y = 4 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        defenceStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        defenceStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        magicStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->magicValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->magicValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        magicStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        magicStatisticTextTexturePosition[i].y = 5 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponMagicDataTextTexturePosition.x = magicStatisticTextTexturePosition[i].x + 140;
        weaponMagicDataTextTexturePosition.y = 5 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        magicStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        magicStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        willStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->willValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->willValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        willStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        willStatisticTextTexturePosition[i].y = 6 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponWillDataTextTexturePosition.x = willStatisticTextTexturePosition[i].x + 140;
        weaponWillDataTextTexturePosition.y = 6 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        willStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        willStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        speedStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->speedValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->speedValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        speedStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        speedStatisticTextTexturePosition[i].y = 7 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponSpeedDataTextTexturePosition.x = speedStatisticTextTexturePosition[i].x + 140;
        weaponSpeedDataTextTexturePosition.y = 7 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        speedStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        speedStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        accuracyStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->accuracyValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->accuracyValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        accuracyStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        accuracyStatisticTextTexturePosition[i].y = 8 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponAccuracyDataTextTexturePosition.x = accuracyStatisticTextTexturePosition[i].x + 140;
        weaponAccuracyDataTextTexturePosition.y = 8 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        accuracyStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        accuracyStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        dodgeRateStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->dodgeRateValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->dodgeRateValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        dodgeRateStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        dodgeRateStatisticTextTexturePosition[i].y = 9 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponDodgeRateDataTextTexturePosition.x = dodgeRateStatisticTextTexturePosition[i].x + 140;
        weaponDodgeRateDataTextTexturePosition.y = 9 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        dodgeRateStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        dodgeRateStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        luckStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->luckValueArray, fontColor));
        TTF_SizeText(mainArialFont, this->luckValueArray, &texteStatCharacterWidth, &texteStatCharacterHeight);
        luckStatisticTextTexturePosition[i].x = (MAXIMUM_SCREEN_WIDTH + 10) / 2;
        luckStatisticTextTexturePosition[i].y = 10 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        weaponLuckDataTextTexturePosition.x = luckStatisticTextTexturePosition[i].x + 140;
        weaponLuckDataTextTexturePosition.y = 10 * (MAXIMUM_SCREEN_HEIGHT - 50) / 11;
        luckStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        luckStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        weaponNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, membersWeaponNames[i].c_str(), fontColor));
        TTF_SizeText(mainArialFont, membersWeaponNames[i].c_str(), &texteStatCharacterWidth, &texteStatCharacterHeight);
        weaponNameStatisticTextTexturePosition[i].x = 150;
        weaponNameStatisticTextTexturePosition[i].y = 100;
        weaponNameStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        weaponNameStatisticTextTexturePosition[i].h = texteStatCharacterHeight;

        firstNameStatisticTextTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, membersFirstNames[i].c_str(), fontColor));
        TTF_SizeText(mainArialFont, membersFirstNames[i].c_str(), &texteStatCharacterWidth, &texteStatCharacterHeight);
        firstNameStatisticTextTexturePosition[i].x = 100;
        firstNameStatisticTextTexturePosition[i].y = 45;
        firstNameStatisticTextTexturePosition[i].w = texteStatCharacterWidth;
        firstNameStatisticTextTexturePosition[i].h = texteStatCharacterHeight;
    }

    const char *tableauEquip[5] = {"Weapon :", "Helmet :", "Body :", "Shield :", "Boots :"};

    for (int i = 0; i < 5; i++)
    {
        equipmentCategoriesNameTextTextures[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, tableauEquip[i], fontColor));
        int texteEquipementWidth = 0;
        int texteEquipementHeight = 0;
        TTF_SizeText(mainArialFont, tableauEquip[i], &texteEquipementWidth, &texteEquipementHeight);
        equipmentCategoriesNameTextTexturesPosition[i].w = texteEquipementWidth;
        equipmentCategoriesNameTextTexturesPosition[i].h = texteEquipementHeight;
        equipmentCategoriesNameTextTexturesPosition[i].x = 0;
        equipmentCategoriesNameTextTexturesPosition[i].y = 100 + i * 30;
    }

    linePosition.x = MAXIMUM_SCREEN_WIDTH / 2;
    linePosition.y = 0;
    linePosition.w = 2;
    linePosition.h = MAXIMUM_SCREEN_HEIGHT;

    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            horizontalLinesPostion[i].x = 0;
            horizontalLinesPostion[i].y = 40;
            horizontalLinesPostion[i].w = MAXIMUM_SCREEN_WIDTH;
            horizontalLinesPostion[i].h = 2;
        }
        else
        {
            horizontalLinesPostion[i].x = 0;
            horizontalLinesPostion[i].y = 260;
            horizontalLinesPostion[i].w = MAXIMUM_SCREEN_WIDTH / 2;
            horizontalLinesPostion[i].h = 2;
        }
    }

    menuTitle = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, "Equipments", fontColor));
    int titreMenuWidth = 0;
    int titreMenuHeight = 0;
    TTF_SizeText(mainArialFont, "Equipments", &titreMenuWidth, &titreMenuHeight);
    menuTitlePosition.x = 0;
    menuTitlePosition.y = 0;
    menuTitlePosition.w = titreMenuWidth;
    menuTitlePosition.h = titreMenuHeight;

    const char *tableauOption[2] = {"Equip", "Remove"};

    for (int i = 0; i < 2; i++)
    {
        menuOptionsNameTexture[i] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, tableauOption[i], fontColor));
        int optionEquipementWidth = 0;
        int optionEquipementHeight = 0;
        TTF_SizeText(mainArialFont, tableauOption[i], &optionEquipementWidth, &optionEquipementHeight);
        menuOptionsNameTexturePosition[i].w = optionEquipementWidth;
        menuOptionsNameTexturePosition[i].h = optionEquipementHeight;
        menuOptionsNameTexturePosition[i].x = ((MAXIMUM_SCREEN_WIDTH + 5) / 2) + i * 150;
        menuOptionsNameTexturePosition[i].y = 0;
    }

    characterPortraitTexturePosition.x = 0;
    characterPortraitTexturePosition.y = 45;
    characterPortraitTexturePosition.w = 50;
    characterPortraitTexturePosition.h = 50;
    characterPortraitSpriteSheetTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/spriteSheets/tof.png"));

    characterPortraitClipPositions[FIRST_TEAM_MEMBER].x = 0;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[FIRST_TEAM_MEMBER].h = 192 / 4;

    characterPortraitClipPositions[SECOND_TEAM_MEMBER].x = 3 * 192 / 4;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].y = 0;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].w = 192 / 4;
    characterPortraitClipPositions[SECOND_TEAM_MEMBER].h = 192 / 4;

    if (!characterPortraitSpriteSheetTexture)
    {
        fprintf(stderr, "An error occured during the tof.png spritesheet loading for the following reason : %s\n", SDL_GetError()); // Écriture de l'erreur
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
            case SDLK_ESCAPE: // Appui sur la touche Echap, on sort du menu pour revenir au jeu
                if (curssorPosition.x >= weaponNameStatisticTextTexturePosition[memberId].x && curssorPosition.x <= linePosition.x && curssorPosition.y >= weaponNameStatisticTextTexturePosition[memberId].y && curssorPosition.y <= horizontalLinesPostion[1].y && counter == 0)
                {
                    curssorPosition.x = menuOptionsNameTexturePosition[EQUIP].x;
                    curssorPosition.y = menuOptionsNameTexturePosition[EQUIP].y;
                    counter = 0;
                    this->playCancelSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x <= linePosition.x && curssorPosition.y <= MAXIMUM_SCREEN_HEIGHT && curssorPosition.y >= horizontalLinesPostion[1].y && counter == 1)
                {
                    curssorPosition.x = weaponNameStatisticTextTexturePosition[memberId].x;
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[memberId].y;
                    counter = 0;
                    flag = 0;
                    this->playCancelSound();
                }
                else if (curssorPosition.x >= weaponNameStatisticTextTexturePosition[memberId].x && curssorPosition.x <= linePosition.x && curssorPosition.y >= weaponNameStatisticTextTexturePosition[memberId].y && curssorPosition.y <= horizontalLinesPostion[1].y && counter == 2)
                {

                    curssorPosition.x = menuOptionsNameTexturePosition[EQUIP].x;
                    curssorPosition.y = menuOptionsNameTexturePosition[EQUIP].y;
                    counter = 0;
                    this->playCancelSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x <= linePosition.x && curssorPosition.y <= MAXIMUM_SCREEN_HEIGHT && curssorPosition.y >= horizontalLinesPostion[1].y && counter == 3)
                {
                    curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].x;
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].y;
                    counter = 0;
                    flag = 0;
                    this->playCancelSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x <= linePosition.x && curssorPosition.y <= MAXIMUM_SCREEN_HEIGHT && curssorPosition.y >= horizontalLinesPostion[1].y && counter == 4)
                {
                    curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[ARMOR].x;
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[ARMOR].y;
                    counter = 0;
                    flag = 0;
                    this->playCancelSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x <= linePosition.x && curssorPosition.y <= MAXIMUM_SCREEN_HEIGHT && curssorPosition.y >= horizontalLinesPostion[1].y && counter == 5)
                {
                    curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[SHIELD].x;
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[SHIELD].y;
                    counter = 0;
                    flag = 0;
                    this->playCancelSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x <= linePosition.x && curssorPosition.y <= MAXIMUM_SCREEN_HEIGHT && curssorPosition.y >= horizontalLinesPostion[1].y && counter == 6)
                {
                    curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[BOOTS].x;
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[BOOTS].y;
                    counter = 0;
                    flag = 0;
                    this->playCancelSound();
                }
                else
                {
                    isWaitingInputs = false;
                    this->playCancelSound();
                }
                break;

            case SDLK_SPACE:
                break;

            case SDLK_RETURN:
                if (curssorPosition.x == menuOptionsNameTexturePosition[EQUIP].x && curssorPosition.y == menuOptionsNameTexturePosition[EQUIP].y)
                {
                    curssorPosition.x = weaponNameStatisticTextTexturePosition[memberId].x;
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[memberId].y;
                    counter = 0;
                    this->playValidationSound();
                }
                else if (curssorPosition.x == menuOptionsNameTexturePosition[REMOVE].x && curssorPosition.y == menuOptionsNameTexturePosition[REMOVE].y)
                {
                    curssorPosition.x = weaponNameStatisticTextTexturePosition[memberId].x;
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[memberId].y;
                    counter = 2;
                    this->playValidationSound();
                }
                else if (curssorPosition.x == weaponNameStatisticTextTexturePosition[memberId].x && curssorPosition.y == weaponNameStatisticTextTexturePosition[memberId].y && counter == 0)
                {
                    weaponsInventorySize = 0;
                    for (int i = 0; i < weaponsInventory.size(); i++)
                    {
                        if (team[memberId]->getEquipableWeaponCategory() == weaponsInventory[i]->GetCategory())
                        {
                            weaponsInventorySize++;
                        }
                    }
                    if (weaponsInventorySize != 0)
                    {
                        counter = 1;
                        k = 0;
                        curssorPosition.x = weaponNameStatisticTextTexturePosition[0].x;
                        curssorPosition.y = weaponNameStatisticTextTexturePosition[0].y;
                        this->playValidationSound();
                    }
                    else
                    {
                        break;
                    }
                }
                else if (curssorPosition.x == weaponNameStatisticTextTexturePosition[memberId].x && curssorPosition.y == weaponNameStatisticTextTexturePosition[memberId].y && counter == 2)
                {
                    string weaponName = NULL;
                    if (team[memberId]->getCharacterClass() == "Chevalier dragon" && team[memberId]->getEquipedWeapon().GetCategory() != "aucun")
                    {
                        Spear *substitut = new Spear(team[memberId]->getEquipedWeapon().GetName(), team[memberId]->getEquipedWeapon().getDamage());
                        weaponsInventory.push_back(substitut);
                        weaponName = substitut->GetName().c_str();
                    }
                    else if (team[memberId]->getCharacterClass() == "Moine" && team[memberId]->getEquipedWeapon().GetCategory() != "aucun")
                    {
                        Glove *substitut = new Glove(team[memberId]->getEquipedWeapon().GetName(), team[memberId]->getEquipedWeapon().getDamage());
                        weaponsInventory.push_back(substitut);
                        weaponName = substitut->GetName().c_str();
                    }

                    Weapon *aucune = new Weapon("aucun");
                    team[memberId]->equipWeapon(*aucune);
                    weaponNameStatisticTextTexture[memberId] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, aucune->GetName().c_str(), fontColor));
                    int texteStatNomArmeWidth = 0;
                    int texteStatNomArmeHeight = 0;
                    TTF_SizeText(mainArialFont, aucune->GetName().c_str(), &texteStatNomArmeWidth, &texteStatNomArmeHeight);
                    weaponNameStatisticTextTexturePosition[memberId].w = texteStatNomArmeWidth;
                    weaponNameStatisticTextTexturePosition[memberId].h = texteStatNomArmeHeight;
                    weaponsInventorySize = weaponsInventory.size();
                    weaponNameStatisticTextTexture[weaponsInventorySize - 1] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, weaponName.c_str(), fontColor));
                    int texteNomArmeWidth = 0;
                    int texteNomArmeHeight = 0;
                    TTF_SizeText(mainArialFont, weaponName.c_str(), &texteNomArmeWidth, &texteNomArmeHeight);
                    weaponNameStatisticTextTexturePosition[memberId].w = texteNomArmeWidth;
                    weaponNameStatisticTextTexturePosition[memberId].h = texteNomArmeHeight;
                    this->playValidationSound();
                }
                else if (curssorPosition.x == memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].x && curssorPosition.y == memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].y && counter == 0)
                {
                    helmetsInventorySize = 0;
                    for (int i = 0; i < helmetsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(helmetsInventory[i]->GetType()))
                        {
                            helmetsInventorySize++;
                        }
                    }

                    if (helmetsInventorySize != 0)
                    {
                        counter = 3;
                        k = 0;
                        curssorPosition.x = armorNameStatisticTextTexturePosition[0].x;
                        curssorPosition.y = armorNameStatisticTextTexturePosition[0].y;
                        this->playValidationSound();
                    }
                    else
                    {
                        break;
                    }
                }
                else if (curssorPosition.x == memberGenericEquipmentNameStatisticTextTexturePosition[ARMOR].x && curssorPosition.y == memberGenericEquipmentNameStatisticTextTexturePosition[ARMOR].y)
                {
                    armorsInventorySize = 0;
                    for (int i = 0; i < armorsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(armorsInventory[i]->GetType()))
                        {
                            armorsInventorySize++;
                        }
                    }

                    if (armorsInventorySize != 0)
                    {
                        counter = 4;
                        k = 0;
                        curssorPosition.x = armorNameStatisticTextTexturePosition[0].x;
                        curssorPosition.y = armorNameStatisticTextTexturePosition[0].y;
                        this->playValidationSound();
                    }
                    else
                    {
                        break;
                    }
                }
                else if (curssorPosition.x == memberGenericEquipmentNameStatisticTextTexturePosition[SHIELD].x && curssorPosition.y == memberGenericEquipmentNameStatisticTextTexturePosition[SHIELD].y)
                {
                    shieldsInventorySize = 0;
                    for (int i = 0; i < shieldsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(shieldsInventory[i]->GetType()))
                        {
                            shieldsInventorySize++;
                        }
                    }

                    if (shieldsInventorySize != 0)
                    {
                        counter = 5;
                        k = 0;
                        curssorPosition.x = shieldNameStatisticTextTexturePosition[0].x;
                        curssorPosition.y = shieldNameStatisticTextTexturePosition[0].y;
                        this->playValidationSound();
                    }
                    else
                    {
                        break;
                    }
                }
                else if (curssorPosition.x == memberGenericEquipmentNameStatisticTextTexturePosition[BOOTS].x && curssorPosition.y == memberGenericEquipmentNameStatisticTextTexturePosition[BOOTS].y)
                {
                    bootsInventorySize = 0;
                    for (int i = 0; i < bootsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(bootsInventory[i]->GetType()))
                        {
                            bootsInventorySize++;
                        }
                    }

                    if (bootsInventorySize != 0)
                    {
                        counter = 6;
                        k = 0;
                        curssorPosition.x = bootNameStatisticTextTexturePosition[0].x;
                        curssorPosition.y = bootNameStatisticTextTexturePosition[0].y;
                        this->playValidationSound();
                    }
                    else
                    {
                        break;
                    }
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x < MAXIMUM_SCREEN_WIDTH / 2 && curssorPosition.y >= weaponNameStatisticTextTexturePosition[0].y && curssorPosition.x <= MAXIMUM_SCREEN_HEIGHT && counter == 1)
                {
                    n = 0;
                    for (int i = 0; i < weaponsInventory.size(); i++)
                    {
                        if (team[memberId]->getEquipableWeaponCategory() == weaponsInventory[i]->GetCategory())
                        {
                            if (curssorPosition.x == weaponNameStatisticTextTexturePosition[abs(i - n)].x && curssorPosition.y == weaponNameStatisticTextTexturePosition[abs(i - n)].y && counter == 1)
                            {
                                vector<Weapon *> copy;
                                copy = weaponsInventory;
                                if (team[memberId]->getCharacterClass() == "Chevalier dragon" && team[memberId]->getEquipedWeapon().GetCategory() != "aucun")
                                {
                                    Spear *substitut = new Spear(team[memberId]->getEquipedWeapon().GetName(), team[memberId]->getEquipedWeapon().getDamage());
                                    copy.push_back(substitut);
                                }
                                else if (team[memberId]->getCharacterClass() == "Moine" && team[memberId]->getEquipedWeapon().GetCategory() != "aucun")
                                {
                                    Glove *substitut = new Glove(team[memberId]->getEquipedWeapon().GetName(), team[memberId]->getEquipedWeapon().getDamage());
                                    copy.push_back(substitut);
                                }

                                team[memberId]->equipWeapon(*weaponsInventory[i]);
                                weaponNameStatisticTextTexture[memberId] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, weaponsInventory[i]->GetName().c_str(), fontColor));
                                int texteStatNomArmeWidth = 0;
                                int texteStatNomArmeHeight = 0;
                                TTF_SizeText(mainArialFont, weaponsInventory[i]->GetName().c_str(), &texteStatNomArmeWidth, &texteStatNomArmeHeight);
                                weaponNameStatisticTextTexturePosition[memberId].w = texteStatNomArmeWidth;
                                weaponNameStatisticTextTexturePosition[memberId].h = texteStatNomArmeHeight;
                                int weaponCounter = 0;
                                l = 0;

                                while (0 != weaponsInventory.size())
                                {
                                    weaponsInventory[weaponCounter] = NULL;
                                    weaponsInventory.pop_back();
                                    weaponCounter++;
                                }

                                for (int j = 0; j < copy.size(); j++)
                                {
                                    if (j != i)
                                    {
                                        weaponsInventory.push_back(copy[j]);
                                        inventoryWeaponsNames[l] = weaponsInventory[l]->GetName();
                                        weaponNameStatisticTextTexture[l] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryWeaponsNames[l].c_str(), fontColor));
                                        int texteNomArmeWidth = 0;
                                        int texteNomArmeHeight = 0;
                                        TTF_SizeText(mainArialFont, inventoryWeaponsNames[l].c_str(), &texteNomArmeWidth, &texteNomArmeHeight);
                                        weaponNameStatisticTextTexturePosition[memberId].w = texteNomArmeWidth;
                                        weaponNameStatisticTextTexturePosition[memberId].h = texteNomArmeHeight;
                                        l++;
                                    }
                                }
                                curssorPosition.x = weaponNameStatisticTextTexturePosition[memberId].x;
                                curssorPosition.y = weaponNameStatisticTextTexturePosition[memberId].y;
                                counter = 0;
                                k = 0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    this->playValidationSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x < MAXIMUM_SCREEN_WIDTH / 2 && curssorPosition.y >= helmetNameStatisticTextTexturePosition[0].y && curssorPosition.x <= MAXIMUM_SCREEN_HEIGHT && counter == 3)
                {
                    n = 0;
                    for (int i = 0; i < helmetsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(helmetsInventory[i]->GetType()))
                        {
                            if (curssorPosition.x == helmetNameStatisticTextTexturePosition[abs(i - n)].x && curssorPosition.y == helmetNameStatisticTextTexturePosition[abs(i - n)].y && counter == 3)
                            {
                                vector<Helmet *> copy;
                                copy = helmetsInventory;
                                if (team[memberId]->getEquipedHelmet().GetType() != "aucun")
                                {
                                    Helmet *substitut = new Helmet(team[memberId]->getEquipedHelmet().GetName(), team[memberId]->getEquipedHelmet().GetType());
                                    copy.push_back(substitut);
                                }

                                if (memberId == FIRST_TEAM_MEMBER)
                                {
                                    team[memberId]->equipHelmet(*helmetsInventory[i]);
                                    team[memberId]->updateArmor(*helmetsInventory[i]);
                                    memberOneArmorNameTextTexture[HELMET] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, helmetsInventory[i]->GetName().c_str(), fontColor));
                                }
                                else if (memberId == SECOND_TEAM_MEMBER)
                                {
                                    team[memberId]->equipHelmet(*helmetsInventory[i]);
                                    team[memberId]->updateArmor(*helmetsInventory[i]);
                                    memberTwoArmorNameTextTexture[HELMET] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, helmetsInventory[i]->GetName().c_str(), fontColor));
                                }
                                int helmetCounter = 0;
                                l = 0;

                                while (0 != helmetsInventory.size())
                                {
                                    helmetsInventory[helmetCounter] = NULL;
                                    helmetsInventory.pop_back();
                                    helmetCounter++;
                                }
                                for (int j = 0; j < copy.size(); j++)
                                {
                                    if (j == i)
                                    {
                                    }
                                    else
                                    {
                                        helmetsInventory.push_back(copy[j]);
                                        inventoryHelmetsNames[l] = helmetsInventory[l]->GetName();
                                        armorNameStatisticTextTexture[l] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryHelmetsNames[l].c_str(), fontColor));
                                        l++;
                                    }
                                }
                                curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[0].x;
                                curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[0].y;
                                counter = 0;
                                k = 0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag = 0;
                    this->playValidationSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x < MAXIMUM_SCREEN_WIDTH / 2 && curssorPosition.y >= armorNameStatisticTextTexturePosition[0].y && curssorPosition.x <= MAXIMUM_SCREEN_HEIGHT && counter == 4)
                {
                    n = 0;
                    for (int i = 0; i < armorsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(armorsInventory[i]->GetType()))
                        {
                            if (curssorPosition.x == armorNameStatisticTextTexturePosition[abs(i - n)].x && curssorPosition.y == armorNameStatisticTextTexturePosition[abs(i - n)].y && counter == 4)
                            {
                                vector<BodyArmor *> copy;
                                copy = armorsInventory;
                                if (team[memberId]->getEquipedArmor().GetType() != "aucun")
                                {
                                    BodyArmor *substitut = new BodyArmor(team[memberId]->getEquipedArmor().GetName(), team[memberId]->getEquipedArmor().GetType());
                                    copy.push_back(substitut);
                                }

                                if (memberId == FIRST_TEAM_MEMBER)
                                {
                                    team[memberId]->equipArmor(*armorsInventory[i]);
                                    team[memberId]->updateArmor(*armorsInventory[i]);
                                    memberOneArmorNameTextTexture[ARMOR] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, armorsInventory[i]->GetName().c_str(), fontColor));
                                }
                                else if (memberId == SECOND_TEAM_MEMBER)
                                {
                                    team[memberId]->equipArmor(*armorsInventory[i]);
                                    team[memberId]->updateArmor(*armorsInventory[i]);
                                    memberTwoArmorNameTextTexture[ARMOR] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, armorsInventory[i]->GetName().c_str(), fontColor));
                                }
                                int armorCounter = 0;
                                l = 0;

                                while (0 != armorsInventory.size())
                                {
                                    armorsInventory[armorCounter] = NULL;
                                    armorsInventory.pop_back();
                                    armorCounter++;
                                }
                                for (int j = 0; j < copy.size(); j++)
                                {
                                    if (j == i)
                                    {
                                    }
                                    else
                                    {
                                        armorsInventory.push_back(copy[j]);
                                        inventoryArmorsNames[l] = armorsInventory[l]->GetName();
                                        armorNameStatisticTextTexture[l] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryArmorsNames[l].c_str(), fontColor));
                                        l++;
                                    }
                                }
                                curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[1].x;
                                curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[1].y;
                                counter = 0;
                                k = 0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag = 0;
                    this->playValidationSound();
                }
                else if (curssorPosition.x >= 0 && curssorPosition.x < MAXIMUM_SCREEN_WIDTH / 2 && curssorPosition.y >= shieldNameStatisticTextTexturePosition[0].y && curssorPosition.x <= MAXIMUM_SCREEN_HEIGHT && counter == 5)
                {
                    n = 0;
                    for (int i = 0; i < shieldsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(shieldsInventory[i]->GetType()))
                        {
                            if (curssorPosition.x == shieldNameStatisticTextTexturePosition[abs(i - n)].x && curssorPosition.y == shieldNameStatisticTextTexturePosition[abs(i - n)].y && counter == 5)
                            {
                                vector<Shield *> copy;
                                copy = shieldsInventory;
                                if (team[memberId]->getEquipedShield().GetType() != "aucun")
                                {
                                    Shield *substitut = new Shield(team[memberId]->getEquipedShield().GetName(), team[memberId]->getEquipedShield().GetType());
                                    copy.push_back(substitut);
                                }

                                if (memberId == FIRST_TEAM_MEMBER)
                                {
                                    team[memberId]->equipShield(*shieldsInventory[i]);
                                    team[memberId]->updateArmor(*shieldsInventory[i]);
                                    memberOneArmorNameTextTexture[SHIELD] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, shieldsInventory[i]->GetName().c_str(), fontColor));
                                }
                                else if (memberId == SECOND_TEAM_MEMBER)
                                {
                                    team[memberId]->equipShield(*shieldsInventory[i]);
                                    team[memberId]->updateArmor(*shieldsInventory[i]);
                                    memberTwoArmorNameTextTexture[SHIELD] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, shieldsInventory[i]->GetName().c_str(), fontColor));
                                }
                                int shieldCounter = 0;
                                l = 0;

                                while (0 != shieldsInventory.size())
                                {
                                    shieldsInventory[shieldCounter] = NULL;
                                    shieldsInventory.pop_back();
                                    shieldCounter++;
                                }
                                for (int j = 0; j < copy.size(); j++)
                                {
                                    if (j == i)
                                    {
                                    }
                                    else
                                    {
                                        shieldsInventory.push_back(copy[j]);
                                        inventoryShieldsNames[l] = shieldsInventory[l]->GetName();
                                        shieldNameStatisticTextTexture[l] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryShieldsNames[l].c_str(), fontColor));
                                        l++;
                                    }
                                }
                                curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[2].x;
                                curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[2].y;
                                counter = 0;
                                k = 0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag = 0;
                    this->playValidationSound();
                }

                else if (curssorPosition.x >= 0 && curssorPosition.x < MAXIMUM_SCREEN_WIDTH / 2 && curssorPosition.y >= bootNameStatisticTextTexturePosition[0].y && curssorPosition.x <= MAXIMUM_SCREEN_HEIGHT && counter == 6)
                {
                    n = 0;
                    for (int i = 0; i < bootsInventory.size(); i++)
                    {
                        if (team[memberId]->IsEquipable(bootsInventory[i]->GetType()))
                        {
                            if (curssorPosition.x == bootNameStatisticTextTexturePosition[abs(i - n)].x && curssorPosition.y == bootNameStatisticTextTexturePosition[abs(i - n)].y && counter == 6)
                            {
                                vector<Boots *> copy;
                                copy = bootsInventory;
                                if (team[memberId]->getEquipedBoots().GetType() != "aucun")
                                {
                                    Boots *substitut = new Boots(team[memberId]->getEquipedBoots().GetName(), team[memberId]->getEquipedBoots().GetType());
                                    copy.push_back(substitut);
                                }

                                if (memberId == FIRST_TEAM_MEMBER)
                                {
                                    team[memberId]->equipBoots(*bootsInventory[i]);
                                    team[memberId]->updateArmor(*bootsInventory[i]);
                                    memberOneArmorNameTextTexture[BOOTS] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, bootsInventory[i]->GetName().c_str(), fontColor));
                                }
                                else if (memberId == SECOND_TEAM_MEMBER)
                                {
                                    team[memberId]->equipBoots(*bootsInventory[i]);
                                    team[memberId]->updateArmor(*bootsInventory[i]);
                                    memberTwoArmorNameTextTexture[BOOTS] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, bootsInventory[i]->GetName().c_str(), fontColor));
                                }
                                int shieldCounter = 0;
                                l = 0;

                                while (0 != bootsInventory.size())
                                {
                                    bootsInventory[shieldCounter] = NULL;
                                    bootsInventory.pop_back();
                                    shieldCounter++;
                                }
                                for (int j = 0; j < copy.size(); j++)
                                {
                                    if (j == i)
                                    {
                                    }
                                    else
                                    {
                                        bootsInventory.push_back(copy[j]);
                                        inventoryBootsNames[l] = bootsInventory[l]->GetName();
                                        bootNameStatisticTextTexture[l] = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, inventoryBootsNames[l].c_str(), fontColor));
                                        l++;
                                    }
                                }
                                curssorPosition.x = memberGenericEquipmentNameStatisticTextTexturePosition[3].x;
                                curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[3].y;
                                counter = 0;
                                k = 0;
                            }
                        }
                        else
                        {
                            n++;
                        }
                    }
                    flag = 0;
                    this->playValidationSound();
                }
                break;

            case SDLK_UP:
                if (curssorPosition.x == weaponNameStatisticTextTexturePosition[memberId].x && curssorPosition.y == weaponNameStatisticTextTexturePosition[memberId].y && (counter == 0 || counter == 2))
                {
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[BOOTS].y;
                    haut = BOOTS;
                    this->playMovementSound();
                }
                else if (curssorPosition.x == memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].x && curssorPosition.y == memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].y && (counter == 0 || counter == 2))
                {
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[memberId].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y >= memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].y && (counter == 0 || counter == 2))
                {
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[--haut].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == weaponNameStatisticTextTexturePosition[0].y && counter == 1)
                {
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[weaponsInventorySize - 1].y;
                    k = weaponsInventorySize - 1;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != weaponNameStatisticTextTexturePosition[0].y && counter == 1)
                {
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[--k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == helmetNameStatisticTextTexturePosition[0].y && counter == 3)
                {
                    curssorPosition.y = helmetNameStatisticTextTexturePosition[helmetsInventorySize - 1].y;
                    k = helmetsInventorySize - 1;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != helmetNameStatisticTextTexturePosition[0].y && counter == 3)
                {
                    curssorPosition.y = helmetNameStatisticTextTexturePosition[--k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == armorNameStatisticTextTexturePosition[0].y && counter == 4)
                {
                    curssorPosition.y = armorNameStatisticTextTexturePosition[armorsInventorySize - 1].y;
                    k = armorsInventorySize - 1;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != armorNameStatisticTextTexturePosition[0].y && counter == 4)
                {
                    curssorPosition.y = armorNameStatisticTextTexturePosition[--k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == shieldNameStatisticTextTexturePosition[0].y && counter == 5)
                {
                    curssorPosition.y = shieldNameStatisticTextTexturePosition[shieldsInventorySize - 1].y;
                    k = shieldsInventorySize - 1;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != shieldNameStatisticTextTexturePosition[0].y && counter == 5)
                {
                    curssorPosition.y = shieldNameStatisticTextTexturePosition[--k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == bootNameStatisticTextTexturePosition[0].y && counter == 6)
                {
                    curssorPosition.y = bootNameStatisticTextTexturePosition[bootsInventorySize - 1].y;
                    k = bootsInventorySize - 1;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != bootNameStatisticTextTexturePosition[0].y && counter == 6)
                {
                    curssorPosition.y = bootNameStatisticTextTexturePosition[--k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.x == menuOptionsNameTexturePosition[REMOVE].x && curssorPosition.y == menuOptionsNameTexturePosition[REMOVE].y)
                {
                    break;
                }
                else if (curssorPosition.x == menuOptionsNameTexturePosition[EQUIP].x && curssorPosition.y == menuOptionsNameTexturePosition[EQUIP].y)
                {
                    break;
                }
                break;

            case SDLK_DOWN:
                if (curssorPosition.x == memberGenericEquipmentNameStatisticTextTexturePosition[BOOTS].x && curssorPosition.y == memberGenericEquipmentNameStatisticTextTexturePosition[BOOTS].y && (counter == 0 || counter == 2))
                {
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[memberId].y;
                    haut = 0;
                    this->playMovementSound();
                }
                else if (curssorPosition.x == weaponNameStatisticTextTexturePosition[memberId].x && curssorPosition.y == weaponNameStatisticTextTexturePosition[memberId].y && (counter == 0 || counter == 2))
                {
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].y;
                    haut = HELMET;
                    this->playMovementSound();
                }
                else if (curssorPosition.y >= memberGenericEquipmentNameStatisticTextTexturePosition[HELMET].y && (counter == 0 || counter == 2))
                {
                    curssorPosition.y = memberGenericEquipmentNameStatisticTextTexturePosition[++haut].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == weaponNameStatisticTextTexturePosition[weaponsInventorySize - 1].y && counter == 1)
                {
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[0].y;
                    k = 0;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != weaponNameStatisticTextTexturePosition[weaponsInventorySize - 1].y && counter == 1)
                {
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[++k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == helmetNameStatisticTextTexturePosition[helmetsInventorySize - 1].y && counter == 3)
                {
                    curssorPosition.y = helmetNameStatisticTextTexturePosition[0].y;
                    k = 0;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != helmetNameStatisticTextTexturePosition[helmetsInventorySize - 1].y && counter == 3)
                {
                    curssorPosition.y = helmetNameStatisticTextTexturePosition[++k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == armorNameStatisticTextTexturePosition[armorsInventorySize - 1].y && counter == 4)
                {
                    curssorPosition.y = armorNameStatisticTextTexturePosition[0].y;
                    k = 0;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != armorNameStatisticTextTexturePosition[armorsInventorySize - 1].y && counter == 4)
                {
                    curssorPosition.y = armorNameStatisticTextTexturePosition[++k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == shieldNameStatisticTextTexturePosition[shieldsInventorySize - 1].y && counter == 5)
                {
                    curssorPosition.y = shieldNameStatisticTextTexturePosition[0].y;
                    k = 0;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != shieldNameStatisticTextTexturePosition[shieldsInventorySize - 1].y && counter == 5)
                {
                    curssorPosition.y = shieldNameStatisticTextTexturePosition[++k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.y == bootNameStatisticTextTexturePosition[bootsInventorySize - 1].y && counter == 6)
                {
                    curssorPosition.y = bootNameStatisticTextTexturePosition[0].y;
                    k = 0;
                    this->playMovementSound();
                }
                else if (curssorPosition.y != bootNameStatisticTextTexturePosition[bootsInventorySize - 1].y && counter == 6)
                {
                    curssorPosition.y = bootNameStatisticTextTexturePosition[++k].y;
                    this->playMovementSound();
                }
                else if (curssorPosition.x == menuOptionsNameTexturePosition[REMOVE].x && curssorPosition.y == menuOptionsNameTexturePosition[REMOVE].y)
                {
                    break;
                }
                else if (curssorPosition.x == menuOptionsNameTexturePosition[EQUIP].x && curssorPosition.y == menuOptionsNameTexturePosition[EQUIP].y)
                {
                    break;
                }
                else
                {
                    curssorPosition.y = weaponNameStatisticTextTexturePosition[++k].y;
                    this->playMovementSound();
                }
                break;

            case SDLK_RIGHT:
                if (curssorPosition.x == menuOptionsNameTexturePosition[REMOVE].x)
                {
                    curssorPosition.x = menuOptionsNameTexturePosition[EQUIP].x;
                    this->playMovementSound();
                }
                else if (curssorPosition.x == menuOptionsNameTexturePosition[EQUIP].x)
                {
                    curssorPosition.x = menuOptionsNameTexturePosition[REMOVE].x;
                    this->playMovementSound();
                }
                break;

            case SDLK_LEFT:
                if (curssorPosition.x == menuOptionsNameTexturePosition[EQUIP].x && counter == 0)
                {
                    curssorPosition.x = menuOptionsNameTexturePosition[REMOVE].x;
                    this->playMovementSound();
                }
                else if (curssorPosition.x == menuOptionsNameTexturePosition[REMOVE].x && counter == 0)
                {
                    curssorPosition.x = menuOptionsNameTexturePosition[EQUIP].x;
                    this->playMovementSound();
                }
                break;

            case SDLK_KP_6:
                if (memberId == (teamMembersSize - 1) && (counter == 0 || counter == 2))
                {
                    memberId = FIRST_TEAM_MEMBER;
                    this->playMovementSound();
                }
                else if (memberId != (teamMembersSize - 1) && (counter == 0 || counter == 2))
                {
                    memberId++;
                    this->playMovementSound();
                }
                else if (counter == 1)
                {
                    break;
                }
                break;

            case SDLK_KP_4:
                if (memberId == FIRST_TEAM_MEMBER && (counter == 0 || counter == 2))
                {
                    memberId = teamMembersSize - 1;
                    this->playMovementSound();
                }
                else if (counter == 1)
                {
                    break;
                }
                else if (memberId != FIRST_TEAM_MEMBER && (counter == 0 || counter == 2))
                {
                    memberId--;
                    this->playMovementSound();
                }
                break;

            default:
                cout << "ok" << endl;
                break;
            }
            break;
        }
        n = 0;
        for (m = 0; m < weaponsInventory.size(); m++)
        {
            if (team[memberId]->getEquipableWeaponCategory() == weaponsInventory[m]->GetCategory())
            {
                if (curssorPosition.y == weaponNameStatisticTextTexturePosition[abs(m - n)].y && counter == 1)
                {
                    sprintf(this->damageValueArray, "+%d", weaponsInventory[m]->getDamage());
                    weaponStrenghtDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, this->damageValueArray, equipmentBonusFontColor));
                    int InfoArmeFrWidth = 0;
                    int InfoArmeFrHeight = 0;
                    TTF_SizeText(mainArialFont, this->damageValueArray, &InfoArmeFrWidth, &InfoArmeFrHeight);
                    weaponStrenghtDataTextTexturePosition.w = InfoArmeFrWidth;
                    weaponStrenghtDataTextTexturePosition.h = InfoArmeFrHeight;
                    flag = 1;
                }
            }
            else
            {
                n++;
            }
        }
        n = 0;
        for (m = 0; m < helmetsInventory.size(); m++)
        {
            if (team[memberId]->IsEquipable(helmetsInventory[m]->GetType()))
            {
                if (curssorPosition.y == helmetNameStatisticTextTexturePosition[abs(m - n)].y && counter == 3)
                {
                    sprintf(helmetDataValueArray, "+%d", helmetsInventory[m]->getPhysicalDefence());
                    weaponDefenceDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, helmetDataValueArray, equipmentBonusFontColor));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(mainArialFont, helmetDataValueArray, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    weaponDefenceDataTextTexturePosition.w = InfoArmeDefWidth;
                    weaponDefenceDataTextTexturePosition.h = InfoArmeDefHeight;
                    sprintf(helmetDataValueArray, "+%d", helmetsInventory[m]->getMagicalDefence());
                    weaponMagicDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, helmetDataValueArray, equipmentBonusFontColor));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(mainArialFont, helmetDataValueArray, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    weaponMagicDataTextTexturePosition.w = InfoArmeMagWidth;
                    weaponMagicDataTextTexturePosition.h = InfoArmeMagHeight;
                    flag = 2;
                }
            }
            else
            {
                n++;
            }
        }
        n = 0;
        for (m = 0; m < armorsInventory.size(); m++)
        {
            if (team[memberId]->IsEquipable(armorsInventory[m]->GetType()))
            {
                if (curssorPosition.y == armorNameStatisticTextTexturePosition[abs(m - n)].y && counter == 4)
                {
                    sprintf(armorDataValueArray, "+%d", armorsInventory[m]->getPhysicalDefence());
                    weaponDefenceDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, armorDataValueArray, equipmentBonusFontColor));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(mainArialFont, armorDataValueArray, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    weaponDefenceDataTextTexturePosition.w = InfoArmeDefWidth;
                    weaponDefenceDataTextTexturePosition.h = InfoArmeDefHeight;
                    sprintf(armorDataValueArray, "+%d", armorsInventory[m]->getMagicalDefence());
                    weaponMagicDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, armorDataValueArray, equipmentBonusFontColor));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(mainArialFont, armorDataValueArray, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    weaponMagicDataTextTexturePosition.w = InfoArmeMagWidth;
                    weaponMagicDataTextTexturePosition.h = InfoArmeMagHeight;
                    flag = 3;
                }
            }
            else
            {
                n++;
            }
        }
        n = 0;
        for (m = 0; m < shieldsInventory.size(); m++)
        {
            if (team[memberId]->IsEquipable(shieldsInventory[m]->GetType()))
            {
                if (curssorPosition.y == shieldNameStatisticTextTexturePosition[abs(m - n)].y && counter == 5)
                {
                    sprintf(shieldDataValueArray, "+%d", shieldsInventory[m]->getPhysicalDefence());
                    weaponDefenceDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, shieldDataValueArray, equipmentBonusFontColor));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(mainArialFont, shieldDataValueArray, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    weaponDefenceDataTextTexturePosition.w = InfoArmeDefWidth;
                    weaponDefenceDataTextTexturePosition.h = InfoArmeDefHeight;
                    sprintf(shieldDataValueArray, "+%d", shieldsInventory[m]->getMagicalDefence());
                    weaponMagicDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, shieldDataValueArray, equipmentBonusFontColor));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(mainArialFont, shieldDataValueArray, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    weaponMagicDataTextTexturePosition.w = InfoArmeMagWidth;
                    weaponMagicDataTextTexturePosition.h = InfoArmeMagHeight;
                    flag = 4;
                }
            }
            else
            {
                n++;
            }
        }
        n = 0;
        for (m = 0; m < bootsInventory.size(); m++)
        {
            if (team[memberId]->IsEquipable(bootsInventory[m]->GetType()))
            {
                if (curssorPosition.y == bootNameStatisticTextTexturePosition[abs(m - n)].y && counter == 6)
                {
                    sprintf(bootDataValueArray, "+%d", bootsInventory[m]->getPhysicalDefence());
                    weaponDefenceDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, bootDataValueArray, equipmentBonusFontColor));
                    int InfoArmeDefWidth = 0;
                    int InfoArmeDefHeight = 0;
                    TTF_SizeText(mainArialFont, bootDataValueArray, &InfoArmeDefWidth, &InfoArmeDefHeight);
                    weaponDefenceDataTextTexturePosition.w = InfoArmeDefWidth;
                    weaponDefenceDataTextTexturePosition.h = InfoArmeDefHeight;
                    sprintf(bootDataValueArray, "+%d", bootsInventory[m]->getMagicalDefence());
                    weaponMagicDataTextTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(mainArialFont, bootDataValueArray, equipmentBonusFontColor));
                    int InfoArmeMagWidth = 0;
                    int InfoArmeMagHeight = 0;
                    TTF_SizeText(mainArialFont, bootDataValueArray, &InfoArmeMagWidth, &InfoArmeMagHeight);
                    weaponMagicDataTextTexturePosition.w = InfoArmeMagWidth;
                    weaponMagicDataTextTexturePosition.h = InfoArmeMagHeight;
                    flag = 5;
                }
            }
            else
            {
                n++;
            }
        }

        displayMenuElements(team, weaponsInventory, helmetsInventory, armorsInventory, shieldsInventory, bootsInventory, memberId, renderer, counter, flag);
    }
    game->setWeaponsInventory(weaponsInventory);
    game->setHelmetsInventory(helmetsInventory);
    game->setArmorsInventory(armorsInventory);
    game->setShieldsInventory(shieldsInventory);
    game->setBootsInventory(bootsInventory);
}

void EquipmentMenu::displayMenuElements(std::vector<Character *> team, std::vector<Weapon *> weaponsInventory, std::vector<Helmet *> helmetsInventory, std::vector<BodyArmor *> armorsInventory, std::vector<Shield *> shieldsInventory, std::vector<Boots *> bootsInventory, int memberId, SDL_Renderer *renderer, int counter, int flag)
{
    // counter = 0 => EQUIPER
    // counter = 2 => ENELVER
    // counter = 1 => ARME
    // counter = 3 => CASQUE
    // counter = 4 => CUIRASSE
    // counter = 5 => BOUCLIER
    // counter = 6 => JAMBIERE
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, &menuPosition);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 36, 70);
    SDL_RenderFillRect(renderer, &curssorPosition);

    std::vector<SDL_Texture *> equipement_name_textures;
    std::vector<SDL_Rect> equipement_name_rectangles;

    for (int i = 0; i < weaponsInventory.size(); i++)
    {
        if (team[memberId]->getEquipableWeaponCategory() == weaponsInventory[i]->GetCategory() && (counter == 0 || counter == 2 || counter == 1))
        {
            equipement_name_textures.push_back(weaponNameInventoryTextTexture[i]);
            equipement_name_rectangles.push_back(weaponNameInventoryTextTexturePosition[i]);
        }
    }

    for (int i = 0; i < helmetsInventory.size(); i++)
    {
        if (team[memberId]->IsEquipable(helmetsInventory[i]->GetType()) && (counter == 0 || counter == 2 || counter == 3))
        {
            equipement_name_textures.push_back(helmetNameStatisticTextTexture[i]);
            equipement_name_rectangles.push_back(helmetNameStatisticTextTexturePosition[i]);
        }
    }

    for (int i = 0; i < armorsInventory.size(); i++)
    {
        if (team[memberId]->IsEquipable(armorsInventory[i]->GetType()) && (counter == 0 || counter == 2 || counter == 4))
        {
            equipement_name_textures.push_back(armorNameStatisticTextTexture[i]);
            equipement_name_rectangles.push_back(armorNameStatisticTextTexturePosition[i]);
        }
    }

    for (int i = 0; i < shieldsInventory.size(); i++)
    {
        if (team[memberId]->IsEquipable(shieldsInventory[i]->GetType()) && (counter == 0 || counter == 2) || counter == 5)
        {
            equipement_name_textures.push_back(shieldNameStatisticTextTexture[i]);
            equipement_name_rectangles.push_back(shieldNameStatisticTextTexturePosition[i]);
        }
    }

    for (int i = 0; i < bootsInventory.size(); i++)
    {
        if (team[memberId]->IsEquipable(bootsInventory[i]->GetType()) && (counter == 0 || counter == 2) || counter == 6)
        {
            equipement_name_textures.push_back(bootNameStatisticTextTexture[i]);
            equipement_name_rectangles.push_back(bootNameStatisticTextTexturePosition[i]);
        }
    }

    for (int i = 0; i < equipement_name_textures.size(); i++)
    {
        SDL_Rect customRectangle;
        customRectangle.x = 0;
        customRectangle.h = equipement_name_rectangles[i].h;
        customRectangle.w = equipement_name_rectangles[i].w;

        if (i == 0)
        {
            customRectangle.y = (i + 1) * 265;
        }
        else
        {
            customRectangle.y = (i + 1) * 265 + 30;
        }

        SDL_RenderCopy(renderer, equipement_name_textures[i], NULL, &customRectangle);
    }

    std::vector<Equipment> equipements = team[memberId]->getEquipedEquipments();

    for (int j = 0; j < equipements.size(); j++)
    {
        if (memberId == FIRST_TEAM_MEMBER)
        {
            SDL_RenderCopy(renderer, memberOneArmorNameTextTexture[j], NULL, &memberGenericEquipmentNameStatisticTextTexturePosition[j]);
        }
        if (memberId == SECOND_TEAM_MEMBER)
        {
            SDL_RenderCopy(renderer, memberTwoArmorNameTextTexture[j], NULL, &memberGenericEquipmentNameStatisticTextTexturePosition[j]);
        }
    }

    SDL_RenderCopy(renderer, hitPointsStatisticTextTexture[memberId], NULL, &hitPointsTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, magicPointsStatisticTextTexture[memberId], NULL, &magicPointsTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, strenghtStatisticTextTexture[memberId], NULL, &strenghtStatisticTextTexturePositio[memberId]);
    SDL_RenderCopy(renderer, defenceStatisticTextTexture[memberId], NULL, &defenceStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, magicStatisticTextTexture[memberId], NULL, &magicStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, willStatisticTextTexture[memberId], NULL, &willStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, speedStatisticTextTexture[memberId], NULL, &speedStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, accuracyStatisticTextTexture[memberId], NULL, &accuracyStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, dodgeRateStatisticTextTexture[memberId], NULL, &dodgeRateStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, luckStatisticTextTexture[memberId], NULL, &luckStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, weaponNameStatisticTextTexture[memberId], NULL, &weaponNameStatisticTextTexturePosition[memberId]);
    SDL_RenderCopy(renderer, firstNameStatisticTextTexture[memberId], NULL, &firstNameStatisticTextTexturePosition[memberId]);

    for (int i = 0; i < 5; i++)
    {
        SDL_RenderCopy(renderer, equipmentCategoriesNameTextTextures[i], NULL, &equipmentCategoriesNameTextTexturesPosition[i]);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &linePosition);

    for (int i = 0; i < 2; i++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &horizontalLinesPostion[i]);
    }

    SDL_RenderCopy(renderer, menuTitle, NULL, &menuTitlePosition);

    for (int i = 0; i < 2; i++)
    {
        SDL_RenderCopy(renderer, menuOptionsNameTexture[i], NULL, &menuOptionsNameTexturePosition[i]);
    }

    SDL_RenderCopy(renderer, characterPortraitSpriteSheetTexture, &characterPortraitClipPositions[memberId], &characterPortraitTexturePosition);

    if (flag == 1)
    {
        SDL_RenderCopy(renderer, weaponStrenghtDataTextTexture, NULL, &weaponStrenghtDataTextTexturePosition);
    }

    if (flag == 2 || flag == 3 || flag == 4 || flag == 5 || flag == 6)
    {
        SDL_RenderCopy(renderer, weaponDefenceDataTextTexture, NULL, &weaponDefenceDataTextTexturePosition);
        SDL_RenderCopy(renderer, weaponMagicDataTextTexture, NULL, &weaponMagicDataTextTexturePosition);
    }

    SDL_RenderPresent(renderer);
}
