#include "inventoryBundle.h"
#include "weapon.h"
#include "helmet.h"
#include "bodyArmor.h"
#include "shield.h"
#include "boots.h"
#include <vector>
using namespace std;

InventoryBundle::InventoryBundle(vector<Weapon *> weaponsInventory,
                                 vector<Helmet *> helmetsInventory,
                                 vector<BodyArmor *> armorsInventory,
                                 vector<Shield *> shieldsInventory,
                                 vector<Boots *> bootsInventory)
{
    this->weaponsInventory = weaponsInventory;
    this->helmetsInventory = helmetsInventory;
    this->armorsInventory = armorsInventory;
    this->shieldsInventory = shieldsInventory;
    this->bootsInventory = bootsInventory;
}

InventoryBundle::InventoryBundle()
{
}

InventoryBundle::~InventoryBundle()
{
}