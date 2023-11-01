#include <string>
#include "resourcesBundle.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <map>
using namespace std;

ResourcesBundle::ResourcesBundle()
{
}

ResourcesBundle::ResourcesBundle(map<string, SDL_Surface *> imageResourceByName, map<string, Mix_Chunk *> soundResourceByName)
{
    this->imageResourceByName = imageResourceByName;
    this->soundResourceByName = soundResourceByName;
}

map<string, SDL_Surface *> ResourcesBundle::getImageResourceByName()
{
    return this->imageResourceByName;
}

void ResourcesBundle::setImageResourceByName(map<string, SDL_Surface *> imageResourceByName)
{
    this->imageResourceByName = imageResourceByName;
}

map<string, Mix_Chunk *> ResourcesBundle::getSoundResourceByName()
{
    return this->soundResourceByName;
}

void ResourcesBundle::setSoundResourceByName(map<string, Mix_Chunk *> soundResourceByName)
{
    this->soundResourceByName = soundResourceByName;
}