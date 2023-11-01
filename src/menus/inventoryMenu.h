#ifndef DEF_INVENTAIRE
#define DEF_INVENTAIRE
#include "../src/dataObjects/character.h"
#include "../src/game/game.h"
#include "../src/menus/menu.h"
#include <freetype/freetype.h>
#include <ft2build.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../src/scenes/menuSceneInterface.h"
#include "../src/dataObjects/resourcesBundle.h"

class InventoryMenu : public MenuSceneInterface
{
public:
    using MenuSceneInterface::MenuSceneInterface;
    InventoryMenu(vector<Resource *> resources, SDL_Renderer *gameRenderer);
    ~InventoryMenu();
    void executeScene(SceneInputData *sceneInputData) override;

protected:
    void initializeDatas(SceneInputData *sceneInputData) override;
    bool detectInputs(SceneInputData *sceneInputData, bool isWaitingForInput) override;
    void renderScene(SceneInputData *sceneInputData) override;
};

#endif
