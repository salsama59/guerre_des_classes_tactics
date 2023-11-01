#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include "../src/game/game.h"
#include <string>
#include <iostream>
#include <vector>
#include "inventoryMenu.h"
using namespace std;

InventoryMenu::InventoryMenu(vector<Resource *> resources, SDL_Renderer *gameRenderer) : MenuSceneInterface(resources, gameRenderer)
{
    cout << "InventoryMenu constructor call";
}

InventoryMenu::~InventoryMenu()
{
}

void InventoryMenu::initializeDatas(SceneInputData *sceneInputData)
{
    cout << "initializeDatas call";
    SDL_Rect menuPosition;
    menuPosition.x = 0;
    menuPosition.y = 0;
    SDL_Texture *menuTexture = SDL_CreateTexture(this->getGameRenderer(),
                                                 SDL_PIXELFORMAT_ARGB8888,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 MAXIMUM_SCREEN_WIDTH, MAXIMUM_SCREEN_HEIGHT);

    SDL_SetRenderDrawColor(this->getGameRenderer(), 180, 180, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->getGameRenderer());

    SDL_RenderCopy(this->getGameRenderer(), menuTexture, NULL, &menuPosition);
}

bool InventoryMenu::detectInputs(SceneInputData *sceneInputData, bool isWaitingForInput)
{
    cout << "detectInputs call";
    SDL_Event inputEvent;
    while (isWaitingForInput)
    {
        SDL_WaitEvent(&inputEvent);
        switch (inputEvent.type)
        {
        case SDL_QUIT:
            isWaitingForInput = false;
            exit(EXIT_SUCCESS);
            atexit(SDL_Quit);

        case SDL_KEYDOWN:
            switch (inputEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isWaitingForInput = false;
                break;
            }
        }
    }
    return isWaitingForInput;
}

void InventoryMenu::renderScene(SceneInputData *sceneInputData)
{
    cout << "renderScene call";
}

void InventoryMenu::executeScene(SceneInputData *sceneInputData)
{
    this->initializeDatas(sceneInputData);
    bool isWaitingForInput = true;
    while (isWaitingForInput)
    {
        isWaitingForInput = this->detectInputs(sceneInputData, isWaitingForInput);
        this->renderScene(sceneInputData);
    }
}