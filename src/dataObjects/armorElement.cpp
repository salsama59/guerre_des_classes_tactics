#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../src/dataObjects/equipment.h"
#include "../src/dataObjects/armorElement.h"
#include <string>
#include <iostream>
using namespace std;

ArmorElement::ArmorElement() : Equipment()
{
    name = "Neant";
    physicalDefence = 0;
    magicalDefence = 0;
    type = "aucun";
    category = "aucun";
}

int ArmorElement::getPhysicalDefence()
{
    return physicalDefence;
}

int ArmorElement::getMagicalDefence()
{
    return magicalDefence;
}
