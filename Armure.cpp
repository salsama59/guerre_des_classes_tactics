#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Equipement.h"
#include "Armure.h"
#include <string>
#include <iostream>
using namespace std;

Armure::Armure(): Equipement()
{
    nom="Neant";
    defPhy= 0;
    defMag=0;
    genre="aucun";
    categorie="aucun";
}

int Armure::GetDefPhy()
{
    return defPhy;
}

int Armure::GetDefMag()
{
    return defMag;
}
