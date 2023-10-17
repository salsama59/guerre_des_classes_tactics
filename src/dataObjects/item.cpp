#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../src/dataObjects/item.h"
#include <string>
#include <iostream>
using namespace std;

Item::Item()
{
}

std::string Item::getName()
{
    return name;
}
