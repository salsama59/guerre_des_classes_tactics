#ifndef DEF_ARME
#define DEF_ARME
#include "Equipement.h"
#include <string>

class Arme: public Equipement
{
    protected:

    int degat;

    public:

    Arme();
    Arme(std::string c);
    int GetDegat();
};

#endif
