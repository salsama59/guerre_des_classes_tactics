#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "equipment.h"
#include "weapon.h"
#include <string>
#include <iostream>
using namespace std;

Weapon::Weapon() : Equipment()
{
    name = "Bare hands";
    damage = 1;
}

Weapon::Weapon(std::string category) : Equipment()
{
    name = "Bare hands";
    damage = 1;
    this->category = category;
}

int Weapon::getDamage()
{
    return damage;
}
