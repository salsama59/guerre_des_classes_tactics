#ifndef DEF_CASQUE
#define DEF_CASQUE
#include "../src/dataObjects/armorElement.h"
#include <string>

class Helmet : public ArmorElement
{
private:
public:
    Helmet();
    Helmet(std::string name, std::string type);
};

#endif
