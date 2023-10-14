#ifndef DEF_JAMBIERE
#define DEF_JAMBIERE
#include "armorElement.h"
#include <string>

class Boots : public ArmorElement
{
private:
public:
    Boots();
    Boots(std::string name, std::string type);
};

#endif
