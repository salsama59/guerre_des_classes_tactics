#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Arme.h"
#include "Lance.h"
#include <string>
#include <iostream>
using namespace std;

Lance::Lance():Arme()
{
    nom="Halebarde";
    categorie="Lance";
    degat= 5;
    poids= 2;
}

Lance::Lance(std::string n, int d):Arme()
{
    nom=n;
    degat=d;
    categorie="Lance";
}
