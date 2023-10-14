#ifndef DEF_POTION
#define DEF_POTION
#include "item.h"
#include <string>

class Potion : public Item
{
private:
    int effect;
    std::string action;

public:
    Potion();
    int GetEffect();
    std::string GetAction();
};

#endif
