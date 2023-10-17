#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "weapon.h"
#include "spear.h"
#include <string>
#include <iostream>
using namespace std;

Spear::Spear() : Weapon()
{
    name = "Halebarde";
    category = "Lance";
    damage = 5;
    weight = 2;
}

Spear::Spear(std::string name, int damage) : Weapon()
{
    this->name = name;
    this->damage = damage;
    this->category = "Lance";
}
