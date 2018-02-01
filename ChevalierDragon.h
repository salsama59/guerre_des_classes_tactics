#ifndef DEF_CHEVALIER_DRAGON
#define DEF_CHEVALIER_DRAGON
#include"Lance.h"
#include"Personnage.h"
#include <string>

class ChevalierDragon : public Personnage
{
    private:

    Lance lance;

    public:

    ChevalierDragon();
    int CriDuDragon(Personnage &cible, ChevalierDragon &attaquant);
    int ChargeDuDragon(Personnage &cible, ChevalierDragon &attaquant);
    int Saut(Personnage &cible, ChevalierDragon &attaquant);
};

#endif
