#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "equipment.h"
#include "armorElement.h"
#include "bodyArmor.h"
#include <string>
#include <iostream>
using namespace std;

BodyArmor::BodyArmor() : ArmorElement()
{
    name = "Kimono";
    type = "Leger";
    category = "Cuirasse";
}

BodyArmor::BodyArmor(std::string name, std::string type) : ArmorElement()
{
    this->name = name;
    this->type = type;
    this->category = "Cuirasse";
}
