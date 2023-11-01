#ifndef DEF_SCENE_INPUT_DATA
#define DEF_SCENE_INPUT_DATA

#include "inventoryBundle.h"
#include "character.h"
using namespace std;

class SceneInputData
{
private:
    vector<Character *> party;
    vector<Character *> team;
    InventoryBundle *inventoryBundle;

public:
    SceneInputData(vector<Character *> party,
                   vector<Character *> team,
                   InventoryBundle *inventoryBundle);
    SceneInputData();
    ~SceneInputData();
    vector<Character *> getParty();
    vector<Character *> getTeam();
    InventoryBundle *getInventoryBundle();
};
#endif