#ifndef DEF_RESOURCES_BUNDLE
#define DEF_RESOURCES_BUNDLE
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>
using namespace std;

class ResourcesBundle
{
private:
    map<string, SDL_Surface *> imageResourceByName;
    map<string, Mix_Chunk *> soundResourceByName;

public:
    ResourcesBundle();
    ResourcesBundle(map<string, SDL_Surface *> imageResourceByName, map<string, Mix_Chunk *> soundResourceByName);
    ~ResourcesBundle();
    map<string, SDL_Surface *> getImageResourceByName();
    void setImageResourceByName(map<string, SDL_Surface *> imageResourceByName);
    map<string, Mix_Chunk *> getSoundResourceByName();
    void setSoundResourceByName(map<string, Mix_Chunk *> soundResourceByName);
};
#endif