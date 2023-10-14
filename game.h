#ifndef DEF_JEU
#define DEF_JEU
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "weapon.h"
#include "helmet.h"
#include "bodyArmor.h"
#include "shield.h"
#include "boots.h"
#include "spear.h"
#include "glove.h"
#include "character.h"
#include <vector>

class Game
{
private:
    SDL_Window *gameWindow;
    SDL_Renderer *gameRenderer;
    std::vector<Weapon *> weaponsInventory;
    std::vector<Helmet *> helmetsInventory;
    std::vector<BodyArmor *> armorInventory;
    std::vector<Shield *> shieldsInventory;
    std::vector<Boots *> bootsInventory;
    std::vector<Character *> party;
    std::vector<Character *> team;

public:
    Game();
    void Jouer();
    SDL_Renderer *getRenderer();
    void setWeaponsInventory(std::vector<Weapon *> newWeaponsInventory);
    void setHelmetsInventory(std::vector<Helmet *> newHelmetsInventory);
    void setArmorsInventory(std::vector<BodyArmor *> newArmorsInventory);
    void setShieldsInventory(std::vector<Shield *> newShieldsInventory);
    void setBootsInventory(std::vector<Boots *> newBootsInventory);
    void setParty(std::vector<Character *> newParty);
    void setTeam(std::vector<Character *> newTeam);
    Game *getObject();
    std::vector<Weapon *> getWeaponsInventory();
    std::vector<Helmet *> getHelmetsInventory();
    std::vector<BodyArmor *> getArmorsInevtory();
    std::vector<Shield *> getShieldsInventory();
    std::vector<Boots *> getBootsInventory();
    std::vector<Character *> getParty();
    std::vector<Character *> getTeam();
};

#endif
