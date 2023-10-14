#include "game.h"
#include "menu.h"
#include "monk.h"
#include "dragonKnight.h"
#include "character.h"
#include "equipment.h"
#include "constants.h"
#include <vector>
#include <iostream>
using namespace std;

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr, "Unable to initialize SDL for the following reason : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE);                                                                          // On quitte le programme
    }

    atexit(SDL_Quit);

    // Ouverture de la fenêtre
    gameWindow = SDL_CreateWindow("Heroic fantasy version demo",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  MAXIMUM_SCREEN_WIDTH, MAXIMUM_SCREEN_HEIGHT,
                                  SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);

    if (gameWindow == NULL || gameRenderer == NULL)
    {
        fprintf(stderr, "Unable to open the window for the following reason : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(gameRenderer, MAXIMUM_SCREEN_WIDTH, MAXIMUM_SCREEN_HEIGHT);

    atexit(SDL_Quit);
}

void Game::Jouer()
{
    Menu *menu = new Menu(*this);
    DragonKnight *dragonKnight = new DragonKnight();
    Monk *monk = new Monk();
    Spear *partisantSpear = new Spear("Partisant", 10);
    Spear *javelinSpear = new Spear("Javelo", 7);
    Glove *leatherKnuckles = new Glove("Gant en cuir", 15);
    Glove *clothKnuckles = new Glove("Gant en tissu", 10);
    Helmet *barbutHelmet = new Helmet("Barbut", "Lourd");
    Helmet *capHelmet = new Helmet("Chapeau", "Leger");
    BodyArmor *rengisArmor = new BodyArmor("Rengis", "Lourd");
    BodyArmor *mantleArmor = new BodyArmor("Manteau", "Leger");
    Shield *targeShield = new Shield("Targe", "Leger");
    Shield *goldShield = new Shield("Bouclier or", "Lourd");
    Boots *silkBoots = new Boots("Botte de soie", "Leger");
    Boots *metalBoots = new Boots("Botte metal", "Lourd");
    helmetsInventory.push_back(barbutHelmet);
    helmetsInventory.push_back(capHelmet);
    armorInventory.push_back(rengisArmor);
    armorInventory.push_back(mantleArmor);
    shieldsInventory.push_back(targeShield);
    shieldsInventory.push_back(goldShield);
    bootsInventory.push_back(silkBoots);
    bootsInventory.push_back(metalBoots);
    weaponsInventory.push_back(partisantSpear);
    weaponsInventory.push_back(javelinSpear);
    weaponsInventory.push_back(leatherKnuckles);
    weaponsInventory.push_back(clothKnuckles);
    party.push_back(monk);
    party.push_back(dragonKnight);
    team.push_back(monk);
    team.push_back(dragonKnight);
    SDL_Rect greenRectanglePosition;
    greenRectanglePosition.x = (MAXIMUM_SCREEN_WIDTH / 2) - (220 / 2);
    greenRectanglePosition.y = (MAXIMUM_SCREEN_HEIGHT / 2) - (180 / 2);
    greenRectanglePosition.w = 220;
    greenRectanglePosition.h = 180;

    SDL_Event inputEvents;
    bool isWaitingInputs = true;

    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gameRenderer);

    SDL_SetRenderDrawColor(gameRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gameRenderer, &greenRectanglePosition);
    SDL_RenderPresent(gameRenderer);

    while (isWaitingInputs)
    {
        SDL_WaitEvent(&inputEvents);
        switch (inputEvents.type)
        {
        case SDL_QUIT:
            isWaitingInputs = false;
            exit(EXIT_SUCCESS);
            atexit(SDL_Quit);

        case SDL_KEYDOWN:
            switch (inputEvents.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                menu->playMainMenuOpeningSound();
                menu->displayMainMenu(team, party, gameRenderer, weaponsInventory, helmetsInventory, armorInventory, shieldsInventory, bootsInventory, this);
                break;

            case SDLK_m:
                menu->playMainMenuOpeningSound();
                menu->displayMainMenu(team, party, gameRenderer, weaponsInventory, helmetsInventory, armorInventory, shieldsInventory, bootsInventory, this);
                break;

            case SDLK_SPACE:
                isWaitingInputs = false;
                break;
            }
            break;
        }

        SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gameRenderer);

        SDL_SetRenderDrawColor(gameRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(gameRenderer, &greenRectanglePosition);
        SDL_RenderPresent(gameRenderer);
    }
}

SDL_Renderer *Game::getRenderer()
{
    return gameRenderer;
}

void Game::setWeaponsInventory(std::vector<Weapon *> newWeaponsInventory)
{
    this->weaponsInventory = newWeaponsInventory;
}

void Game::setHelmetsInventory(std::vector<Helmet *> newHelmetsInventory)
{
    this->helmetsInventory = newHelmetsInventory;
}

void Game::setArmorsInventory(std::vector<BodyArmor *> newArmorsInventory)
{
    this->armorInventory = newArmorsInventory;
}

void Game::setShieldsInventory(std::vector<Shield *> newShieldsInventory)
{
    this->shieldsInventory = newShieldsInventory;
}

void Game::setBootsInventory(std::vector<Boots *> newBootsInventory)
{
    this->bootsInventory = newBootsInventory;
}

void Game::setParty(std::vector<Character *> newParty)
{
    this->party = newParty;
}

void Game::setTeam(std::vector<Character *> newTeam)
{
    this->team = newTeam;
}

std::vector<Weapon *> Game::getWeaponsInventory()
{
    return weaponsInventory;
}

std::vector<Helmet *> Game::getHelmetsInventory()
{
    return helmetsInventory;
}

std::vector<BodyArmor *> Game::getArmorsInevtory()
{
    return armorInventory;
}

std::vector<Shield *> Game::getShieldsInventory()
{
    return shieldsInventory;
}

std::vector<Boots *> Game::getBootsInventory()
{
    return bootsInventory;
}

std::vector<Character *> Game::getParty()
{
    return party;
}

std::vector<Character *> Game::getTeam()
{
    return team;
}

Game *Game::getObject()
{
    return this;
}
