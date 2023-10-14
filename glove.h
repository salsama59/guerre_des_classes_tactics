#ifndef DEF_GANT
#define DEF_GANT

#include <string>
#include "weapon.h"

class Glove : public Weapon
{
private:
public:
    Glove();
    Glove(std::string name, int damage);
};

#endif
