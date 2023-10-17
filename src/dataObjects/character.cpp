#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../src/dataObjects/character.h"
#include "../src/constants/constants.h"
#include "../enums/armorTypesEnum.h"
#include <string>
#include <iostream>
using namespace std;

// Définition du constructeur de la classe personnage
Character::Character()
{
    surname = "roman";
    firstName = "jose";
    hitPoint = 150;
    magicPoint = 20;
    strenght = 5;
    defence = 3;
    level = 1;
    maximumHitPoint = 150;
    maximumMagicPoint = 20;
    experience = 0;
    nextLevelExperience = 100;
}

// Surdéfinition du constructeur de la classe personnage
Character::Character(string surname, string firstName)
{
    this->surname = surname;
    this->firstName = firstName;
    hitPoint = 150;
    magicPoint = 20;
    strenght = 4;
    defence = 2;
    level = 1;
    maximumHitPoint = 150;
    maximumMagicPoint = 20;
    experience = 0;
    nextLevelExperience = 100;
}

// Fonction permettant à un personnage d'attaquer
void Character::attack(Character &target, Character &attacker, Weapon &weaponUsed)
{
    // Appel de la fonction permettant de recevoir des dégats
    target.receiveDamages(equipedWeapon.getDamage(), attacker.strenght);
}

// Définition d'une fonction permettant à un personnage de recevoir des dégats normaux
int Character::receiveDamages(int weaponDamage, int opponentStrenght)
{
    int baseDamage = 0, damageDealt = 0;
    baseDamage = weaponDamage + opponentStrenght;
    damageDealt = baseDamage - (defence + equipedHelmet.getPhysicalDefence() + equipedArmor.getPhysicalDefence() + equipedShield.getPhysicalDefence() + equipedBoots.getPhysicalDefence());
    if (damageDealt < 0)
    {
        damageDealt = 0;
    }

    hitPoint -= damageDealt;

    if (hitPoint < 0)
    {
        hitPoint = 0;
    }

    return (damageDealt);
}

// Définition d'une fonction permettant à un personnage de recevoir des dégats spéciaux
int Character::receiveSpecialDamages(int weaponDamage, int opponentCaracteristic, int baseDamageCalculation, std::string damageType)
{
    int baseDamage = 0, damageDealt = 0;

    if (damageType == "phy")
    {
        // calcul permettant d'obtenir les dégats du combat
        baseDamage = weaponDamage + opponentCaracteristic + baseDamageCalculation;
        // calcul permettant d'obtenir les dégats réels subits par les personnages
        damageDealt = baseDamage - (defence + equipedHelmet.getPhysicalDefence() + equipedArmor.getPhysicalDefence() + equipedShield.getPhysicalDefence() + equipedBoots.getPhysicalDefence());

        // Test permettant d'éviter les dégats négatifs
        if (damageDealt < 0)
        {
            damageDealt = 0;
        }

        hitPoint -= damageDealt;
        // Test permettant d'éviter les points de vie négatifs
        if (hitPoint < 0)
        {
            hitPoint = 0;
        }
    }
    else if (damageType == "mag")
    {
        // calcul permettant d'obtenir les dégats du combat
        baseDamage = opponentCaracteristic + baseDamageCalculation;

        // calcul permettant d'obtenir les dégats réels subits par les personnages
        damageDealt = baseDamage - (willPower + equipedHelmet.getMagicalDefence() + equipedArmor.getMagicalDefence() + equipedShield.getMagicalDefence() + equipedBoots.getMagicalDefence());

        // Test permettant d'éviter les dégats négatifs
        if (damageDealt < 0)
        {
            damageDealt = 0;
        }

        hitPoint -= damageDealt;
        // Test permettant d'éviter les points de vie négatifs
        if (hitPoint < 0)
        {
            hitPoint = 0;
        }
    }
    else if (damageType == "ryuken")
    {
        // calcul permettant d'obtenir les dégats du combat
        baseDamage = opponentCaracteristic + baseDamageCalculation;
        // calcul permettant d'obtenir les dégats réels subits par les personnages
        damageDealt = baseDamage - (willPower + equipedHelmet.getMagicalDefence() + equipedArmor.getMagicalDefence() + equipedShield.getMagicalDefence() + equipedBoots.getMagicalDefence());

        // Test permettant d'éviter les dégats négatifs
        if (damageDealt < 0)
        {
            damageDealt = 0;
        }

        magicPoint -= damageDealt;
        hitPoint -= damageDealt;
        // Test permettant d'éviter les points de vie négatifs
        if (hitPoint < 0)
        {
            hitPoint = 0;
        }
        // Test permettant d'éviter les points de magie négatifs
        if (magicPoint < 0)
        {
            magicPoint = 0;
        }
    }
    return (damageDealt);
}

// Définition d'une fonction permettant l'affichage du status du personnage
void Character::statisticMenuDisplay()
{
    cout << "     STATUS      " << endl;
    cout << "" << endl;
    cout << "Nom : " << surname << endl;
    cout << "Prenom : " << firstName << endl;
    cout << "PV: " << hitPoint << endl;
    cout << "PM : " << magicPoint << endl;
    cout << "FORCE : " << strenght << endl;
    cout << "DEFENSE : " << defence << endl;
    cout << "MAGIE : " << magic << endl;
    cout << "VOLONTE : " << willPower << endl;
    cout << "NIVEAU : " << level << endl;
    cout << "EXPERIENCE : " << experience << endl;
    cout << "EXPERIENCE POUR LE PROCHAIN NIVEAU : " << nextLevelExperience << endl;
    cout << "ARME EQUIPE : " << equipedWeapon.GetName() << endl;
    cout << "" << endl;
}

int Character::gainStrenght(int bonus)
{
    strenght += bonus;
    return bonus;
}

int Character::gainDodgeRate(int bonus)
{
    dodgeRate += bonus;
    return bonus;
}

int Character::gainHitPoints(int bonus)
{
    hitPoint += bonus;
    return bonus;
}

int Character::gainMagicPoints(int bonus)
{
    magicPoint += bonus;
    return bonus;
}

int Character::gainLuck(int bonus)
{
    luck += bonus;
    return bonus;
}

int Character::gainAccuracy(int bonus)
{
    accuracy += bonus;
    return bonus;
}

int Character::gainDefense(int bonus)
{
    defence += bonus;
    return bonus;
}

int Character::gainWillPower(int bonus)
{
    willPower += bonus;
    return bonus;
}

int Character::gainSpeed(int bonus)
{
    speed += bonus;
    return bonus;
}

int Character::gainLevel(int bonus)
{
    level += bonus;
    return bonus;
}

int Character::gainMagic(int bonus)
{
    magic += bonus;
    return bonus;
}

int Character::setNextLevelExperience(int newValue)
{
    nextLevelExperience = newValue;
    return nextLevelExperience;
}

int Character::gainExperience(int gain)
{
    experience += gain;
    return gain;
}

void Character::equipWeapon(Weapon &newWeapon)
{
    equipedWeapon = newWeapon;
}

void Character::equipHelmet(Helmet &newHelmet)
{
    equipedHelmet = newHelmet;
}

void Character::equipArmor(BodyArmor &newArmor)
{
    equipedArmor = newArmor;
}

void Character::equipShield(Shield &newShield)
{
    equipedShield = newShield;
}

void Character::equipBoots(Boots &newBoots)
{
    equipedBoots = newBoots;
}

int Character::useItem(Character &target, Potion &item)
{
    std::string action;
    int effect = 0;
    action = item.GetAction();
    effect = item.GetEffect();
    if (action == "PV")
    {
        target.gainHitPoints(effect);
        if (target.hitPoint > target.maximumHitPoint)
        {
            target.hitPoint = target.maximumHitPoint;
        }
    }

    else if (action == "PM")
    {
        target.gainMagicPoints(effect);
        if (target.magicPoint > target.maximumMagicPoint)
        {
            target.magicPoint = target.maximumMagicPoint;
        }
    }

    return effect;
}

void Character::levelUp()
{
    int thresholds[4], i = 1;
    // Tab contient les différents seuils d'expérience du personnage (ceci évoluera dans la version final)
    thresholds[0] = 30;
    thresholds[1] = 100;
    thresholds[2] = 200;
    thresholds[3] = 300;

    // Boucle permettant l'augmentation du niveau tant que le seuil est dépassé
    while (experience >= nextLevelExperience)
    {
        this->gainLevel(1);
        this->gainHitPoints(10);
        this->gainMagicPoints(2);
        this->gainStrenght(3);
        this->gainDefense(5);
        this->gainWillPower(1);
        this->setNextLevelExperience(thresholds[i++]);
        if (experience < nextLevelExperience)
        {
            cout << "LE PERSONNAGE " << firstName << " EST PASSE AU NIVEAU " << level << endl;
            cout << "" << endl;
        }
    }
}

int Character::getHitPoints()
{
    return hitPoint;
}

int Character::getMagicPoints()
{
    return magicPoint;
}

int Character::getMaximumHitPoints()
{
    return maximumHitPoint;
}

int Character::getMaximumMagicPoints()
{
    return maximumMagicPoint;
}

int Character::getExperience()
{
    return experience;
}

int Character::getNextLevelExperiencePoints()
{
    return nextLevelExperience;
}

int Character::getStrenght()
{
    return strenght;
}

int Character::getDefence()
{
    return defence;
}

int Character::getMagic()
{
    return magic;
}

int Character::getWillPower()
{
    return willPower;
}

int Character::getSpeed()
{
    return speed;
}

float Character::getDodgeRate()
{
    return dodgeRate;
}

float Character::getAccuracy()
{
    return accuracy;
}

int Character::getLuck()
{
    return luck;
}

int Character::getLevel()
{
    return level;
}

std::string Character::getSurname()
{
    return surname;
}

std::string Character::getFirstName()
{
    return firstName;
}

std::string Character::getCharacterClass()
{
    return characterClass;
}

Weapon Character::getEquipedWeapon()
{
    return equipedWeapon;
}

Helmet Character::getEquipedHelmet()
{
    return equipedHelmet;
}

BodyArmor Character::getEquipedArmor()
{
    return equipedArmor;
}

Shield Character::getEquipedShield()
{
    return equipedShield;
}

Boots Character::getEquipedBoots()
{
    return equipedBoots;
}

std::vector<Equipment> Character::getEquipedEquipments()
{
    return equipedEquipments;
}

std::string Character::getEquipableWeaponCategory()
{
    return equipableWeaponCategory;
}

std::string *Character::getEquipableArmorCategories()
{
    return equipableArmorCategories;
}

bool Character::IsEquipable(std::string category)
{
    if (category == equipableArmorCategories[0])
    {
        return true;
    }
    else if (category == equipableArmorCategories[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Character::updateArmor(ArmorElement &armorPiece)
{
    if (armorPiece.GetCategory() == "Casque")
    {
        equipedEquipments[HELMET] = armorPiece;
    }
    else if (armorPiece.GetCategory() == "Cuirasse")
    {
        equipedEquipments[ARMOR] = armorPiece;
    }
    else if (armorPiece.GetCategory() == "Bouclier")
    {
        equipedEquipments[SHIELD] = armorPiece;
    }
    else if (armorPiece.GetCategory() == "Jambiere")
    {
        equipedEquipments[BOOTS] = armorPiece;
    }
}
