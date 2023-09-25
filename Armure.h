#ifndef DEF_ARMURE
#define DEF_ARMURE
#include <string>
#include "Equipement.h"

class Armure: public Equipement {
    protected:

    int defPhy;
    int defMag;

    public:

    Armure();
    int GetDefPhy();
    int GetDefMag();
};

#endif
