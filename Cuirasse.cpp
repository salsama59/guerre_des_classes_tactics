#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Equipement.h"
#include "Armure.h"
#include "Cuirasse.h"
#include <string>
#include <iostream>
using namespace std;

Cuirasse::Cuirasse(): Armure()
{
    nom="Kimono";
    genre="Leger";
    categorie="Cuirasse";
}

Cuirasse::Cuirasse(std::string n, std::string g): Armure()
{
    nom=n;
    genre=g;
    categorie="Cuirasse";
}
