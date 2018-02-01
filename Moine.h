#ifndef DEF_MOINE
#define DEF_MOINE
#include"Gant.h"
#include"Personnage.h"
#include <string>

class Moine : public Personnage
{
    private:

    Gant gant;

    public:

    Moine();
    int Aura(Personnage &cible, Moine &attaquant);
    int Chakra(Personnage &cible, Moine &attaquant);
    int Concentration(Moine &cible, Moine &attaquant);

};

#endif
