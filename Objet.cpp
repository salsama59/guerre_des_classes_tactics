#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Objet.h"
#include <string>
#include <iostream>
using namespace std;

Objet::Objet()
{

}

std::string Objet::GetNom()
{
    return nom;
}

