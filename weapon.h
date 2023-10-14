#ifndef DEF_ARME
#define DEF_ARME
#include "equipment.h"
#include <string>

class Weapon : public Equipment
{
protected:
    int damage;

public:
    Weapon();
    Weapon(std::string category);
    int getDamage();
};

#endif
