#ifndef DEF_ETAT
#define DEF_ETAT
#include "../src/dataObjects/character.h"
#include "../src/menus/menu.h"
#include "../src/constants/constants.h"
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

class StatusMenu : public Menu
{
private:
    char strenghtValueArray[STATISTICS_ARRAY_SIZE];
    char defenceValueArray[STATISTICS_ARRAY_SIZE];
    char willValueArray[STATISTICS_ARRAY_SIZE];
    char accuracyValueArray[STATISTICS_ARRAY_SIZE];
    char dodgeRateValueArray[STATISTICS_ARRAY_SIZE];
    char luckValueArray[STATISTICS_ARRAY_SIZE];
    char speedValueArray[STATISTICS_ARRAY_SIZE];
    char magicValueArray[STATISTICS_ARRAY_SIZE];
    SDL_Texture *strenghtStatisticTextTexture[4];
    SDL_Texture *defenceStatisticTextTexture[4];
    SDL_Texture *magicStatisticTextTexture[4];
    SDL_Texture *willStatisticTextTexture[4];
    SDL_Texture *speedStatisticTextTexture[4];
    SDL_Texture *accuracyStatisticTextTexture[4];
    SDL_Texture *dodgeRateStatisticTextTexture[4];
    SDL_Texture *luckStatisticTextTexture[4];
    SDL_Texture *nameStatisticTextTexture[4];
    SDL_Texture *weaponNameTextTexture[4];
    SDL_Texture *memberOneArmorNameTextTexture[4];
    SDL_Texture *memberTwoArmorNameTextTexture[4];
    SDL_Texture *memberThreeArmorNameTextTexture[4];
    SDL_Texture *memberFourArmorNameTextTexture[4];
    SDL_Texture *equipmentNameTextTextures[5];
    SDL_Surface *line;
    SDL_Surface *horizontalLines[4];
    const char *equipementCategoriesTitle[5];
    SDL_Rect strenghtStatisticTextTexturePosition[4];
    SDL_Rect defenceStatisticTextTexturePosition[4];
    SDL_Rect magicStatisticTextTexturePosition[4];
    SDL_Rect willStatisticTextTexturePosition[4];
    SDL_Rect speedStatisticTextTexturePosition[4];
    SDL_Rect accuracyStatisticTextTexturePosition[4];
    SDL_Rect dodgeRateStatisticTextTexturePosition[4];
    SDL_Rect luckStatisticTextTexturePosition[4];
    SDL_Rect lastNamStatisticTextTexturePosition[4];
    SDL_Rect hitPointsTextTexturePosition[4];
    SDL_Rect magicPointsTextTexturePosition[4];
    SDL_Rect experiencePointsTextTexturePosition[4];
    SDL_Rect firstNameStatisticTextTexturePosition[4];
    SDL_Rect levelTextTexturePosition[4];
    SDL_Rect weaponNameTextTexturePosition[4];
    SDL_Rect armorNameTextTexturePosition[4];
    SDL_Rect equipmentNameTextTexturesPosition[5];
    SDL_Rect chararacterPortraitPosition;

public:
    StatusMenu(SDL_Renderer *ecran);

    void displayStatusMenu(std::vector<Character *> team, SDL_Renderer *renderer);

    void displayMenuElements(std::vector<Character *> team, int memberId, SDL_Renderer *renderer);
};

#endif
