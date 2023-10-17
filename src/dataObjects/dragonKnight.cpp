#include <SDL2/SDL_image.h>
#include "character.h"
#include <string>
#include <iostream>
#include "dragonKnight.h"
#include "spear.h"
#include "helmet.h"
#include <vector>
using namespace std;

DragonKnight::DragonKnight() : Character()
{
    surname = "DRAGNIR";
    firstName = "Sherao";
    characterClass = "Chevalier dragon";
    hitPoint = 200;
    magicPoint = 50;
    strenght = 20;
    defence = 20;
    magic = 15;
    willPower = 10;
    speed = 20;
    luck = 5;
    dodgeRate = 11.5;
    accuracy = 100;
    level = 1;
    experience = 0;
    nextLevelExperience = 30;
    maximumHitPoint = 200;
    maximumMagicPoint = 50;
    Spear weapon;
    equipedWeapon = weapon;
    Helmet *helmet = new Helmet("Casque or", "Lourd");
    equipedHelmet = *helmet;
    equipedEquipments.push_back(equipedHelmet);
    equipedEquipments.push_back(equipedArmor);
    equipedEquipments.push_back(equipedShield);
    equipedEquipments.push_back(equipedBoots);
    equipableWeaponCategory = "Lance";
    equipableArmorCategories[0] = "Standard";
    equipableArmorCategories[1] = "Lourd";
}

int DragonKnight::dragonRoar(Character &target, DragonKnight &attacker)
{
    int grantedBonus = 0, consumption = 40;
    if (attacker.magicPoint - consumption < 0)
    {
        cout << "Not enough MP" << endl;
        return grantedBonus;
    }
    else
    {
        grantedBonus = attacker.level * 5;
        target.gainStrenght(grantedBonus);
        attacker.magicPoint -= consumption;
        return grantedBonus;
    }
}

int DragonKnight::dragonTackle(Character &target, DragonKnight &attacker)
{
    int baseCalculation = 0, result = 0;
    baseCalculation = attacker.level * 10;
    result = target.receiveSpecialDamages(0, attacker.magic, baseCalculation, "ryuken");
    attacker.gainHitPoints(result);
    attacker.gainMagicPoints(result);
    if (attacker.hitPoint > attacker.maximumHitPoint)
    {
        attacker.hitPoint = attacker.maximumHitPoint;
    }
    if (attacker.magicPoint > attacker.maximumMagicPoint)
    {
        attacker.magicPoint = attacker.maximumMagicPoint;
    }
    return result;
}

int DragonKnight::jump(Character &target, DragonKnight &attacker)
{
    int baseCalculation = 0, result = 0;
    baseCalculation = (attacker.strenght + attacker.speed) / 2;
    result = target.receiveSpecialDamages(equipedWeapon.getDamage(), attacker.strenght, baseCalculation, "phy");
    return result;
}
