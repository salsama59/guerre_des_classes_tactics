#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../src/dataObjects/equipment.h"
#include "../src/dataObjects/armorElement.h"
#include "../src/dataObjects/shield.h"
#include <string>
#include <iostream>
using namespace std;

Shield::Shield() : ArmorElement()
{
}

Shield::Shield(std::string name, std::string type) : ArmorElement()
{
    this->name = name;
    this->type = type;
    this->category = "Bouclier";
}
