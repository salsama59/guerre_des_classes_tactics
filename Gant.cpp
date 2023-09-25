#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Arme.h"
#include "Gant.h"
#include <string>
#include <iostream>
using namespace std;

Gant::Gant():Arme()
{
    nom="Cestus";
    categorie="Gant";
    degat= 7;
    poids= 0.5;
}

Gant::Gant(std::string n, int d):Arme()
{
    nom=n;
    degat=d;
    categorie="Gant";
}
