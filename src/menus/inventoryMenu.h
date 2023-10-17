#ifndef DEF_INVENTAIRE
#define DEF_INVENTAIRE
#include "../src/dataObjects/character.h"
#include "../src/game/game.h"
#include "../src/menus/menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class InventoryMenu : public Menu
{
private:
    void displayMenuElements();

public:
    InventoryMenu(Game &game);
    ~InventoryMenu();
    void displayInventory();
};

#endif
