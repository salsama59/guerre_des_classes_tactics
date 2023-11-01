#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include "menuSceneInterface.h"
using namespace std;

/*
Modifier le constructeur pour en avoir un qui prend des booleen en parametre pour savoir si l'audio doit être chargé, ou le moteur graphique ou alors le moteur de police.
ces booleen seron des propriété de l'interface et utilisé pour savoir si le destructeur doit oui ou non tenter de détruire les resources pour libérer la mémoire.
Créer une classe ressource (chemin et type en propriété, le type sera une enum )
passer une liste de ressource à la fonction loadresources (la fonction va boucler sur les resources et les charger et stocker les ressources dans une hasmap)
définir une hasmap qui contiendra les resources dans l'interface.
définir un objet de configuration de scene qui utilisera le polymorphisme pour changer d'attribut en fonction de l'implementation permetant ainsi de passer un seul objet et de le manipuler différement suivant les types de scenes
passer la fonction executeScene en non virtuel et definir en la faisant appeler dans l'ordre initializeDatas detectInputs renderScene lestrois prendron en parametre l'objet de configuration abstrait qui sera rendu concret selon l'implementation.
*/

MenuSceneInterface::MenuSceneInterface(vector<Resource *> resources, SDL_Renderer *gameRenderer)
{
    cout << "MenuSceneInterface constructor call";
    this->isEngineEnabled = true;
    this->isAudioEnabled = true;
    this->gameRenderer = gameRenderer;
    this->resourcesBundle = new ResourcesBundle({}, {});
    this->loadSoundSystem();
    this->loadEngine();
    this->loadResources(resources);
}

MenuSceneInterface::MenuSceneInterface(bool isAudioEnabled, bool isEngineEnabled, vector<Resource *> resources, SDL_Renderer *gameRenderer)
{
    this->isEngineEnabled = isEngineEnabled;
    this->isAudioEnabled = isAudioEnabled;
    this->gameRenderer = gameRenderer;
    this->resourcesBundle = new ResourcesBundle({}, {});
    this->loadResources(resources);

    if (this->isAudioEnabled)
    {
        this->loadSoundSystem();
    }

    if (this->isEngineEnabled)
    {
        this->loadEngine();
    }
}

MenuSceneInterface::~MenuSceneInterface()
{
    if (this->isAudioEnabled)
    {
        Mix_CloseAudio();
    }

    if (this->isEngineEnabled)
    {
        TTF_Quit();
    }
}

void MenuSceneInterface::loadSoundSystem()
{
    SDL_AudioSpec audioSpec;
    audioSpec.freq = MIX_DEFAULT_FREQUENCY;
    audioSpec.format = MIX_DEFAULT_FORMAT;
    audioSpec.channels = MIX_DEFAULT_CHANNELS;
    int channelNumber = 4;
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 15) < 0)
    {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        exit(2);
    }
    else
    {
        Mix_QuerySpec(&audioSpec.freq, &audioSpec.format, &channelNumber);
        SDL_Log("Opened audio at %d Hz %d bit%s %s audio buffer\n", audioSpec.freq,
                (audioSpec.format & 0xFF),
                (SDL_AUDIO_ISFLOAT(audioSpec.format) ? " (float)" : ""),
                (audioSpec.channels > 2) ? "surround" : (audioSpec.channels > 1) ? "stereo"
                                                                                 : "mono");
    }

    /* Set the music volume */
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void MenuSceneInterface::loadEngine()
{
    int trueTypeFontInitializationResult = TTF_Init();

    if (trueTypeFontInitializationResult == -1)
    {
        fprintf(stderr, "An error occured during SDL_TTF initialization for the following reason : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }
}

void MenuSceneInterface::loadResources(vector<Resource *> resources)
{
    cout << "loadResources call";

    map<string, SDL_Surface *> loadedImageByName = this->getResourcesBundle()->getImageResourceByName();
    map<string, Mix_Chunk *> loadedSoundByName = this->getResourcesBundle()->getSoundResourceByName();

    for (int i = 0; i < resources.size(); i++)
    {
        switch (resources[i]->getType())
        {
        case IMAGE:
        {
            SDL_Surface *loadedImage = IMG_Load(resources[i]->getPath().c_str());

            if (loadedImage == NULL)
            {
                SDL_Log("Couldn't open the image file %s : %s\n", resources[i]->getPath().c_str(), SDL_GetError());
                exit(2);
            }
            else
            {
                cout << "image resource loaded";
                loadedImageByName[resources[i]->getName()] = loadedImage;
            }
            break;
        }
        case SOUND:
        {
            Mix_Chunk *loadedSound = Mix_LoadWAV(resources[i]->getPath().c_str());

            if (loadedSound == NULL)
            {
                SDL_Log("Couldn't open audio file %s : %s\n", resources[i]->getPath().c_str(), SDL_GetError());
                exit(2);
            }
            else
            {
                loadedSoundByName[resources[i]->getName()] = loadedSound;
            }

            break;
        }
        default:
        {
            cout << "unknown resource type : " << resources[i]->getType() << '\n';
            break;
        }
        }
    }

    this->resourcesBundle->setImageResourceByName(loadedImageByName);
    this->resourcesBundle->setSoundResourceByName(loadedSoundByName);
}

ResourcesBundle *MenuSceneInterface::getResourcesBundle()
{
    return this->resourcesBundle;
}

SDL_Renderer *MenuSceneInterface::getGameRenderer()
{
    return this->gameRenderer;
}