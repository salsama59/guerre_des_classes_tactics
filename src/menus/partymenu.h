#ifndef DEF_GROUPE
#define DEF_GROUPE
#include "../src/dataObjects/character.h"
#include "../src/game/game.h"
#include "../src/menus/menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class PartyMenu : public Menu
{
private:
    SDL_Texture *horizontalLines[4];
    SDL_Rect hitPointsStatiticPositions[4];
    SDL_Rect magicPointsStatiticPositions[4];
    void displayMenuElements(std::vector<Character *> team, SDL_Renderer *renderer);

public:
    PartyMenu(SDL_Renderer *renderer);
    ~PartyMenu();
    void displayPartyMenu(std::vector<Character *> party, std::vector<Character *> team, SDL_Renderer *renderer, Game *game);
};

#endif
