#ifndef DEF_CUIRASSE
#define DEF_CUIRASSE
#include "armorElement.h"
#include <string>

class BodyArmor : public ArmorElement
{
private:
public:
    BodyArmor();
    BodyArmor(std::string name, std::string type);
};

#endif
