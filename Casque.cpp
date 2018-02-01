#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Equipement.h"
#include "Armure.h"
#include "Casque.h"
#include <string>
#include <iostream>
using namespace std;

Casque::Casque(): Armure()
{
    nom="Bandeau";
    genre="Standard";
    categorie="Casque";
}

Casque::Casque(std::string n, std::string g): Armure()
{
    nom=n;
    genre=g;
    categorie="Casque";
}
