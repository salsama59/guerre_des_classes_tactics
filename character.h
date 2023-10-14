#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE
#include "weapon.h"
#include "helmet.h"
#include "bodyArmor.h"
#include "shield.h"
#include "boots.h"
#include "potion.h"
#include <string>
#include <vector>

class Character
{
protected:
    std::string surname;
    std::string firstName;
    std::string characterClass;
    std::string equipableWeaponCategory;
    std::string equipableArmorCategories[2];
    int hitPoint;
    int magicPoint;
    int strenght;
    int defence;
    int magic;
    int willPower;
    int speed;
    int luck;
    float dodgeRate;
    float accuracy;
    int level;
    int maximumHitPoint;
    int maximumMagicPoint;
    int experience;
    int nextLevelExperience;
    Weapon equipedWeapon;
    Helmet equipedHelmet;
    Shield equipedShield;
    BodyArmor equipedArmor;
    Boots equipedBoots;
    std::vector<Equipment> equipedEquipments;

public:
    Character();
    Character(std::string surname, std::string firstName);
    void attack(Character &target, Character &attacker, Weapon &weaponUsed);
    int receiveDamages(int weaponDamages, int opponentStrenght);
    int receiveSpecialDamages(int weaponDamages, int characterStatistic, int baseDamageCalculation, std::string damageType);
    void statisticMenuDisplay();
    virtual int gainStrenght(int bonus);
    virtual int gainHitPoints(int bonus);
    virtual int gainMagicPoints(int bonus);
    virtual int gainDefense(int bonus);
    virtual int gainLuck(int bonus);
    virtual int gainMagic(int bonus);
    virtual int gainWillPower(int bonus);
    virtual int gainSpeed(int bonus);
    virtual int gainDodgeRate(int bonus);
    virtual int gainAccuracy(int bonus);
    virtual int gainLevel(int bonus);
    virtual int gainExperience(int experience);
    virtual int setNextLevelExperience(int newValue);
    void equipWeapon(Weapon &newWeapon);
    void equipHelmet(Helmet &newHelmet);
    void equipArmor(BodyArmor &newArmor);
    void equipShield(Shield &newShield);
    void equipBoots(Boots &newBoots);
    void updateArmor(ArmorElement &equipmentPiece);
    int useItem(Character &target, Potion &item);
    void levelUp();
    int getLevel();
    std::string getSurname();
    std::string getFirstName();
    std::string getCharacterClass();
    int getHitPoints();
    int getMagicPoints();
    int getMaximumHitPoints();
    int getMaximumMagicPoints();
    int getExperience();
    int getNextLevelExperiencePoints();
    int getStrenght();
    int getDefence();
    int getMagic();
    int getWillPower();
    int getSpeed();
    float getDodgeRate();
    float getAccuracy();
    int getLuck();
    Weapon getEquipedWeapon();
    Helmet getEquipedHelmet();
    BodyArmor getEquipedArmor();
    Shield getEquipedShield();
    Boots getEquipedBoots();
    std::vector<Equipment> getEquipedEquipments();
    std::string getEquipableWeaponCategory();
    std::string *getEquipableArmorCategories();
    bool IsEquipable(std::string type);
};

#endif
