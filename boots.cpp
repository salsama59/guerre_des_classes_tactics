#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "equipment.h"
#include "armorElement.h"
#include "boots.h"
#include <string>
#include <iostream>
using namespace std;

Boots::Boots() : ArmorElement()
{
    name = "Sandales";
    type = "Standard";
    category = "Jambiere";
}

Boots::Boots(std::string name, std::string type) : ArmorElement()
{
    this->name = name;
    this->type = type;
    this->category = "Jambiere";
}
