#ifndef DEF_MENU
#define DEF_MENU
#include "../src/dataObjects/character.h"
#include "../src/game/game.h"
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../src/constants/constants.h"
#include <string>
#include <vector>
class Menu
{
protected:
    char maximumHitPointValueArray[STATISTICS_ARRAY_SIZE];
    char maximumMagicPointValueArray[STATISTICS_ARRAY_SIZE];
    char experienceArray[STATISTICS_ARRAY_SIZE];
    char levelArray[STATISTICS_ARRAY_SIZE];
    int largeur;      // Largeur du menu
    int hauteur;      // hauteur du menu
    int largeurCur;   // Largeur du cursseur
    int hauteurCur;   // hauteur du cursseur
    Uint32 menuColor; // Couleur du menu
    Uint32 cursorColor;
    Uint32 lineColor;
    SDL_Color fontColor;
    SDL_Color equipmentBonusFontColor;
    SDL_Texture *characterPortraitSpriteSheetTexture;
    SDL_Texture *partyCharacterPortraitSpriteSheetTexture;
    SDL_Texture *menuTitle;
    SDL_Texture *cursor;      // Cursseur permettant la navigation dans le menu
    SDL_Texture *menuTexture; // Fenetre du menu
    SDL_Renderer *renderer;   // Pointeur vers la fenetre principale
    SDL_Texture *hitPointsStatisticTextTexture[4];
    SDL_Texture *magicPointsStatisticTextTexture[4];
    SDL_Texture *experienceStatisticTextTexture[4];
    SDL_Texture *firstNameStatisticTextTexture[4];
    SDL_Texture *levelStatisticTextTexture[4];
    SDL_Texture *menuItemTextTexture[9];
    SDL_Texture *ligne;
    SDL_Texture *HorizontalLines[4];
    SDL_Rect curssorPosition; // Position du cursseur dans le menu
    SDL_Rect menuTitlePosition;
    SDL_Rect menuPosition; // Position de la fenêtre du menu
    SDL_Rect menuItemTextTexturePosition[9];
    SDL_Rect hitPointsStatisticTextTexturePosition[4];
    SDL_Rect magicPointsStatisticTextTexturePosition[4];
    SDL_Rect experienceStatisticTextTextureposition[4];
    SDL_Rect firstNameStatisticTextTexturePosition[4];
    SDL_Rect levelStatisticTextTexturePosition[4];
    SDL_Rect characterPortraitSpriteSheetTexturePositions[4];
    SDL_Rect partyCharacterPortraitSpriteSheetTexturePositions[4];
    SDL_Rect linePosition;
    SDL_Rect horizontalLinePosition[4];
    SDL_Rect characterPortraitClipPositions[4];
    SDL_Rect partyCharacterPortraitClipPositions[4];
    SDL_Event inputEvent;         // Variable permettant la gestion des évènements dans le menu
    Mix_Chunk *moveSound;         // Son lors du déplacement du cursseur dans le  menu
    Mix_Chunk *validationSound;   // Son lors de la validation
    Mix_Chunk *cancelationSound;  // Son lors de l'annulation
    Mix_Chunk *menuOpeningSound;  // Son lors de l'entrée dans le menu
    TTF_Font *mainArialFont;      // Police de caractère utilisé dans le menu
    TTF_Font *secondaryArialFont; // Police de caractère utilisé dans le menu
    int curssorSpeed;             // Vitesse de déplacement du cursseur

public:
    Menu(Game &game);
    Menu();
    ~Menu();
    void playMovementSound();
    void playValidationSound();
    void playCancelSound();
    void playMainMenuOpeningSound();
    void displayMainMenu(std::vector<Character *> team, std::vector<Character *> party, SDL_Renderer *renderer, std::vector<Weapon *> weaponsInventory, std::vector<Helmet *> helmetsInventory, std::vector<BodyArmor *> armorsInventory, std::vector<Shield *> shieldsInventory, std::vector<Boots *> bootsInventory, Game *game);

private:
    void displayMenuElements(std::vector<std::string> menuItems, std::vector<Character *> team);
};

#endif
