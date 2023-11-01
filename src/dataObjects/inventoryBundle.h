#ifndef DEF_INVENTORY_BUNDLE
#define DEF_INVENTORY_BUNDLE
#include "weapon.h"
#include "helmet.h"
#include "bodyArmor.h"
#include "shield.h"
#include "boots.h"
#include <vector>
using namespace std;

class InventoryBundle
{
private:
    vector<Weapon *> weaponsInventory;
    vector<Helmet *> helmetsInventory;
    vector<BodyArmor *> armorsInventory;
    vector<Shield *> shieldsInventory;
    vector<Boots *> bootsInventory;

public:
    InventoryBundle(vector<Weapon *> weaponsInventory,
                    vector<Helmet *> helmetsInventory,
                    vector<BodyArmor *> armorsInventory,
                    vector<Shield *> shieldsInventory,
                    vector<Boots *> bootsInventory);
    InventoryBundle();
    ~InventoryBundle();
};
#endif