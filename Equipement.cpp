#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
