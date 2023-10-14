#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "equipment.h"
#include <string>
#include <iostream>
using namespace std;

Equipment::Equipment()
{
}

std::string Equipment::GetName()
{
    return name;
}

std::string Equipment::GetType()
{
    return type;
}

std::string Equipment::GetCategory()
{
    return category;
}
