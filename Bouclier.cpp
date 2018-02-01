#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Equipement.h"
#include "Armure.h"
#include "Bouclier.h"
#include <string>
#include <iostream>
using namespace std;

Bouclier::Bouclier(): Armure()
{

}

Bouclier::Bouclier(std::string n, std::string g): Armure()
{
    nom=n;
    genre=g;
    categorie="Bouclier";
}
