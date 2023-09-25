#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Equipement.h"
#include "Armure.h"
#include "Jambiere.h"
#include <string>
#include <iostream>
using namespace std;

Jambiere::Jambiere(): Armure()
{
   nom= "Sandales";
   genre="Standard";
   categorie="Jambiere";
}

Jambiere::Jambiere(std::string n, std::string g): Armure()
{
    nom=n;
    genre=g;
    categorie="Jambiere";
}

