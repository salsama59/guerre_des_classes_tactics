#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "weapon.h"
#include "glove.h"
#include <string>
#include <iostream>
using namespace std;

Glove::Glove() : Weapon()
{
    name = "Cestus";
    category = "Gant";
    damage = 7;
    weight = 0.5;
}

Glove::Glove(std::string name, int damage) : Weapon()
{
    this->name = name;
    this->damage = damage;
    this->category = "Gant";
}
