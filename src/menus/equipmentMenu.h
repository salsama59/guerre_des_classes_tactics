#ifndef DEF_SMENUEQUIPEMENT
#define DEF_SMENUEQUIPEMENT
#include "../src/dataObjects/character.h"
#include "../src/menus/menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class EquipmentMenu : public Menu
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
    char damageValueArray[STATISTICS_ARRAY_SIZE];
    char helmetDataValueArray[STATISTICS_ARRAY_SIZE];
    char armorDataValueArray[STATISTICS_ARRAY_SIZE];
    char shieldDataValueArray[STATISTICS_ARRAY_SIZE];
    char bootDataValueArray[STATISTICS_ARRAY_SIZE];
    SDL_Texture *menuOptionsNameTexture[3];
    SDL_Texture *strenghtStatisticTextTexture[4];
    SDL_Texture *defenceStatisticTextTexture[4];
    SDL_Texture *magicStatisticTextTexture[4];
    SDL_Texture *willStatisticTextTexture[4];
    SDL_Texture *speedStatisticTextTexture[4];
    SDL_Texture *accuracyStatisticTextTexture[4];
    SDL_Texture *dodgeRateStatisticTextTexture[4];
    SDL_Texture *luckStatisticTextTexture[4];
    SDL_Texture *weaponStrenghtDataTextTexture;
    SDL_Texture *weaponDefenceDataTextTexture;
    SDL_Texture *weaponMagicDataTextTexture;
    SDL_Texture *weaponWillDataTextTexture;
    SDL_Texture *weaponSpeedDataTextTexture;
    SDL_Texture *weaponAccuracyDataTextTexture;
    SDL_Texture *weaponDodgeRateDataTextTexture;
    SDL_Texture *weaponLuckDataTextTexture;
    SDL_Texture *weaponHitPointsDataTextTexture;
    SDL_Texture *weaponMagicPointsDataTextTexture;
    SDL_Texture *firstNameStatisticTextTexture[4];
    SDL_Texture *weaponDamageStatisticTextTexture[5];
    SDL_Texture *weaponNameStatisticTextTexture[5];
    SDL_Texture *armorNameStatisticTextTexture[5];
    SDL_Texture *helmetNameStatisticTextTexture[5];
    SDL_Texture *shieldNameStatisticTextTexture[5];
    SDL_Texture *bootNameStatisticTextTexture[5];
    SDL_Texture *weaponNameInventoryTextTexture[5];
    SDL_Texture *memberOneArmorNameTextTexture[4];
    SDL_Texture *memberTwoArmorNameTextTexture[4];
    SDL_Texture *equipmentCategoriesNameTextTextures[5];
    SDL_Texture *horizontalLines[4];
    SDL_Rect menuOptionsNameTexturePosition[3];
    SDL_Rect strenghtStatisticTextTexturePositio[4];
    SDL_Rect defenceStatisticTextTexturePosition[4];
    SDL_Rect magicStatisticTextTexturePosition[4];
    SDL_Rect willStatisticTextTexturePosition[4];
    SDL_Rect speedStatisticTextTexturePosition[4];
    SDL_Rect accuracyStatisticTextTexturePosition[4];
    SDL_Rect dodgeRateStatisticTextTexturePosition[4];
    SDL_Rect luckStatisticTextTexturePosition[4];
    SDL_Rect hitPointsTextTexturePosition[4];
    SDL_Rect magicPointsTextTexturePosition[4];
    SDL_Rect weaponStrenghtDataTextTexturePosition;
    SDL_Rect weaponDefenceDataTextTexturePosition;
    SDL_Rect weaponMagicDataTextTexturePosition;
    SDL_Rect weaponWillDataTextTexturePosition;
    SDL_Rect weaponSpeedDataTextTexturePosition;
    SDL_Rect weaponAccuracyDataTextTexturePosition;
    SDL_Rect weaponDodgeRateDataTextTexturePosition;
    SDL_Rect weaponLuckDataTextTexturePosition;
    SDL_Rect weaponHitPointsDataTextTexturePosition;
    SDL_Rect weaponMagicPointsDataTextTexturePosition;
    SDL_Rect horizontalLinesPostion[2];
    SDL_Rect weaponNameStatisticTextTexturePosition[5];
    SDL_Rect armorNameStatisticTextTexturePosition[5];
    SDL_Rect helmetNameStatisticTextTexturePosition[5];
    SDL_Rect bootNameStatisticTextTexturePosition[5];
    SDL_Rect shieldNameStatisticTextTexturePosition[5];
    SDL_Rect weaponDamageStatisticTextTexturePosition[4];
    SDL_Rect weaponNameInventoryTextTexturePosition[5];
    SDL_Rect memberGenericEquipmentNameStatisticTextTexturePosition[5];
    SDL_Rect equipmentCategoriesNameTextTexturesPosition[5];
    SDL_Rect characterPortraitTexturePosition;

public:
    EquipmentMenu(SDL_Renderer *renderer);
    ~EquipmentMenu();
    void displayEquipmentMenu(std::vector<Character *> team, SDL_Renderer *renderer, std::vector<Weapon *> weaponsInventory, std::vector<Helmet *> helmetsInventory, std::vector<BodyArmor *> armorsInventory, std::vector<Shield *> shieldsInventory, std::vector<Boots *> bootsInventory, Game *game);

private:
    void displayMenuElements(std::vector<Character *> team, std::vector<Weapon *> weaponsInventory, std::vector<Helmet *> helmetsInventory, std::vector<BodyArmor *> armorsInventory, std::vector<Shield *> shieldsInventory, std::vector<Boots *> bootsInventory, int memberId, SDL_Renderer *renderer, int counter, int flag);
};

#endif
