#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Equipement.h"
#include "Arme.h"
#include <string>
#include <iostream>
using namespace std;

Arme::Arme(): Equipement()
{
    nom="Main nues";
    degat= 1;
}

Arme::Arme(std::string c): Equipement()
{
    nom="Main nues";
    degat= 1;
    categorie=c;
}

int Arme::GetDegat()
{
    return degat;
}
