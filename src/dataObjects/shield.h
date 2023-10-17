#ifndef DEF_BOUCLIER
#define DEF_BOUCLIER
#include "../src/dataObjects/armorElement.h"
#include <string>

class Shield : public ArmorElement
{
private:
public:
    Shield();
    Shield(std::string name, std::string type);
};

#endif
