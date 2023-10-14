#ifndef DEF_ARMURE
#define DEF_ARMURE
#include <string>
#include "equipment.h"

class ArmorElement: public Equipment {
    protected:

    int physicalDefence;
    int magicalDefence;

    public:

    ArmorElement();
    int getPhysicalDefence();
    int getMagicalDefence();
};

#endif
