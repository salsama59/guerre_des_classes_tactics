#include "sceneInputData.h"
#include "inventoryBundle.h"
#include "character.h"
using namespace std;

SceneInputData::SceneInputData(vector<Character *> party,
                               vector<Character *> team,
                               InventoryBundle *inventoryBundle)
{
    this->party = party;
    this->team = team;
    this->inventoryBundle = inventoryBundle;
}

SceneInputData::SceneInputData()
{
}

SceneInputData::~SceneInputData()
{
}

vector<Character *> SceneInputData::getParty()
{
    return this->party;
}

vector<Character *> SceneInputData::getTeam()
{
    return this->team;
}

InventoryBundle *SceneInputData::getInventoryBundle()
{
    return this->inventoryBundle;
}