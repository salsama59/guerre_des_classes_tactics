#include <SDL2/SDL_image.h>
#include "character.h"
#include "monk.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Monk::Monk() : Character()
{
    surname = "ALMONI";
    firstName = "Sheryfa";
    characterClass = "Moine";
    hitPoint = 150;
    magicPoint = 90;
    strenght = 25;
    defence = 15;
    magic = 25;
    willPower = 20;
    speed = 35;
    luck = 10;
    dodgeRate = 30.5;
    accuracy = 100;
    level = 1;
    experience = 0;
    nextLevelExperience = 15;
    maximumHitPoint = 150;
    maximumMagicPoint = 90;
    Glove weapon;
    equipedWeapon = weapon;
    equipedEquipments.push_back(equipedHelmet);
    equipedEquipments.push_back(equipedArmor);
    equipedEquipments.push_back(equipedShield);
    equipedEquipments.push_back(equipedBoots);
    equipableWeaponCategory = "Gant";
    equipableArmorCategories[0] = "Standard";
    equipableArmorCategories[1] = "Leger";
}

int Monk::aura(Character &target, Monk &attacker)
{
    int baseCalculation = 0, result = 0, consumption = 25;
    if (attacker.magicPoint - consumption < 0)
    {
        cout << "Not enough MP" << endl;
        ;
        return result;
    }
    else
    {
        baseCalculation = (attacker.strenght + attacker.magic) / 2;
        result = target.receiveSpecialDamages(equipedWeapon.getDamage(), attacker.strenght, baseCalculation, "phy");
    }

    return result;
}

int Monk::chakra(Character &target, Monk &attacker)
{
    int bonus = 0, consumption = 20;
    if (attacker.magicPoint - consumption < 0)
    {
        cout << "Vous n'avez pas assez de PM" << endl;
        ;
        return bonus;
    }
    else
    {
        bonus = attacker.magic + (attacker.magic * 0.5);
        target.gainHitPoints(bonus);
        target.gainMagicPoints(bonus / 2);
        if (attacker.hitPoint > attacker.maximumHitPoint)
        {
            attacker.hitPoint = attacker.maximumHitPoint;
        }
        if (attacker.magicPoint > attacker.maximumMagicPoint)
        {
            attacker.magicPoint = attacker.maximumMagicPoint;
        }
        return bonus;
    }
}

int Monk::concentration(Monk &target, Monk &attacker)
{
    int bonus = 0, consumption = 30;
    if (attacker.magicPoint - consumption < 0)
    {
        cout << "Vous n'avez pas assez de PM" << endl;
        ;
        return bonus;
    }
    else
    {
        bonus = ((target.strenght + target.magic) / 2) * 0.25;
        target.gainStrenght(bonus);
        target.gainMagic(bonus);
        return bonus;
    }
}
