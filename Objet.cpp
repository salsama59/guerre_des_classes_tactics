#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

