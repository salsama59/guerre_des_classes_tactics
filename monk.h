#ifndef DEF_MOINE
#define DEF_MOINE
#include "glove.h"
#include "character.h"
#include <string>

class Monk : public Character
{
private:
    Glove glove;

public:
    Monk();
    int aura(Character &target, Monk &attacker);
    int chakra(Character &target, Monk &attacker);
    int concentration(Monk &target, Monk &attacker);
};

#endif
