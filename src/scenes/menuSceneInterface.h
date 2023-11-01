#ifndef DEF_MENU_SCENE_INTERFACE
#define DEF_MENU_SCENE_INTERFACE
#include "../dataObjects/resource.h"
#include "../dataObjects/resourcesBundle.h"
#include "../dataObjects/sceneInputData.h"
#include <vector>
#include <map>
using namespace std;

class MenuSceneInterface
{
public:
    MenuSceneInterface(vector<Resource *> resources, SDL_Renderer *gameRenderer);
    MenuSceneInterface(bool isAudioEnabled, bool isEngineEnabled, vector<Resource *> resources, SDL_Renderer *gameRenderer);
    virtual ~MenuSceneInterface();
    virtual void executeScene(SceneInputData *sceneInputData) = 0;

private:
    bool isAudioEnabled;
    bool isEngineEnabled;
    ResourcesBundle *resourcesBundle;
    SDL_Renderer *gameRenderer;
    void loadSoundSystem();
    void loadEngine();
    void loadResources(vector<Resource *> resources);

protected:
    virtual void initializeDatas(SceneInputData *sceneInputData) = 0;
    virtual bool detectInputs(SceneInputData *sceneInputData, bool isWaitingForInput) = 0;
    virtual void renderScene(SceneInputData *sceneInputData) = 0;
    ResourcesBundle *getResourcesBundle();
    SDL_Renderer *getGameRenderer();
};

#endif