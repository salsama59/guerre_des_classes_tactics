#ifndef DEF_POTION
#define DEF_POTION
#include "Objet.h"
#include <string>

class Potion: public Objet
{
    private:

    int effet;
    std::string action;
    public:

    Potion();
    int GetEffet();
    std::string GetAction();
};

#endif
