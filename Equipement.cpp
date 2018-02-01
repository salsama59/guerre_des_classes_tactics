#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Equipement.h"
#include <string>
#include <iostream>
using namespace std;

Equipement::Equipement()
{

}

std::string Equipement::GetNom()
{
    return nom;
}

std::string Equipement::GetGenre()
{
    return genre;
}

std::string Equipement::GetCategorie()
{
    return categorie;
}
