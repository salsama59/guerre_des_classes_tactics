#ifndef DEF_LANCE
#define DEF_LANCE

#include <string>
#include "weapon.h"

class Spear : public Weapon
{
private:
public:
    Spear();
    Spear(std::string name, int damage);
};

#endif
