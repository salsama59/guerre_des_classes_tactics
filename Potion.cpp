#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "item.h"
#include "potion.h"
#include <string>
#include <iostream>
using namespace std;

Potion::Potion() : Item()
{
    name = "Elixir";
    effect = 50;
    action = "PV";
}

int Potion::GetEffect()
{
    return effect;
}

std::string Potion::GetAction()
{
    return action;
}
