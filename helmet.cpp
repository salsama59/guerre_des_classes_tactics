#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "equipment.h"
#include "armorElement.h"
#include "helmet.h"
#include <string>
#include <iostream>
using namespace std;

Helmet::Helmet() : ArmorElement()
{
    name = "Bandeau";
    type = "Standard";
    category = "Casque";
}

Helmet::Helmet(std::string name, std::string type) : ArmorElement()
{
    this->name = name;
    this->type = type;
    this->category = "Casque";
}
