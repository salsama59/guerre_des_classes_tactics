#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Objet.h"
#include "Potion.h"
#include <string>
#include <iostream>
using namespace std;

Potion::Potion(): Objet()
{
    nom="Elixir";
    effet=50;
    action="PV";
}

int Potion::GetEffet()
{
    return effet;
}

std::string Potion::GetAction()
{
    return action;
}
