#ifndef DEF_CHEVALIER_DRAGON
#define DEF_CHEVALIER_DRAGON
#include "../src/dataObjects/spear.h"
#include "../src/dataObjects/character.h"
#include <string>

class DragonKnight : public Character
{
private:
    Spear spear;

public:
    DragonKnight();
    int dragonRoar(Character &target, DragonKnight &attacker);
    int dragonTackle(Character &target, DragonKnight &attacker);
    int jump(Character &target, DragonKnight &attacker);
};

#endif