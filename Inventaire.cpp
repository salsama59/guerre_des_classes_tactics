#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include "Inventaire.h"
#include "Jeu.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Inventaire::Inventaire(Jeu &j)
{
    largeur=640;
    hauteur=480;
    ecran=j.GetFen();
    //couleur= SDL_MapRGB(ecran->format, 180, 180, 180);
    //fenMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    positionMenu.x=0;
    positionMenu.y=0;
    fenMenu = SDL_CreateTexture(ecran,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               largeur, hauteur);
    //Modification de la couleur du fond
    SDL_SetRenderDrawColor(ecran, 180, 180, 180, 0xFF );
    SDL_RenderCopy(ecran, fenMenu, NULL, &positionMenu);
    SDL_RenderClear(ecran);
    //SDL_FillRect(fenMenu, NULL, couleur);

    SDL_AudioSpec spec;
    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;
    int channelNumber = 4;
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 15) < 0) {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        exit(2);
    } else {
        Mix_QuerySpec(&spec.freq, &spec.format, &channelNumber);
        SDL_Log("Opened audio at %d Hz %d bit%s %s audio buffer\n", spec.freq,
            (spec.format&0xFF),
            (SDL_AUDIO_ISFLOAT(spec.format) ? " (float)" : ""),
            (spec.channels > 2) ? "surround" : (spec.channels > 1) ? "stereo" : "mono");
    }

     /* Set the music volume */
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    Mix_Music *music = NULL;
    sonDeplacement = Mix_LoadWAV("deplacement.mp3");
    sonValidation = Mix_LoadWAV("validation.wav");
    sonAnnulation = Mix_LoadWAV("annulation.wav");
}

Inventaire:: ~Inventaire()
{
    Mix_FreeChunk(sonDeplacement);
    Mix_FreeChunk(sonValidation);
    Mix_FreeChunk(sonAnnulation);
}

void Inventaire::AffichageInventaire()
{
    int cycle=1, init=0, i=0, t=0, j=0;
    init=TTF_Init();
    if(init == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        atexit(TTF_Quit);
    }

    police = TTF_OpenFont("arial.ttf", 30);
    couleurCarac = {255, 255, 255};
    //TTF_SetFontStyle(police, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);

    //couleurCursseur= SDL_MapRGB(ecran->format, 255, 255, 36);
    positionCursseur.w=185;
    positionCursseur.h=35;
    positionCursseur.x=0;
    positionCursseur.y=0;
    //cursseur= SDL_CreateRGBSurface(SDL_HWSURFACE, positionCursseur.w, positionCursseur.h, 32, 0, 0, 0, 0);
    //SDL_FillRect(cursseur, NULL, couleurCursseur);
    //SDL_SetAlpha(cursseur, SDL_SRCALPHA, 70);
    cursseur = SDL_CreateTexture(ecran,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               positionCursseur.w, positionCursseur.h);
    //Modification de la couleur du fond
    SDL_SetRenderDrawColor(ecran, 255, 255, 36, 70 );
    SDL_RenderCopy(ecran, cursseur, NULL, &positionCursseur);
    SDL_RenderClear(ecran);
    while (cycle)
    {
        SDL_WaitEvent(&action);
        switch(action.type)
        {
            case SDL_QUIT :
            cycle = 0;
            exit(EXIT_SUCCESS);
            atexit(SDL_Quit);

            case SDL_KEYDOWN:
            switch (action.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appui sur la touche Echap, on sort du menu pour revenir au jeu
                cycle = 0;
                break;

                case SDLK_SPACE:
                break;

                case SDLK_UP:

                break;

                case SDLK_DOWN:

                break;
            }
            break;
        }

        // Collage de la surface de menu sur l'écran
        //SDL_BlitSurface(fenMenu, NULL, ecran, &positionMenu);

        //SDL_BlitSurface(cursseur, NULL, ecran, &positionCursseur);
        //Mise à jour de l'affichage
        //SDL_Flip(ecran);
        SDL_RenderPresent(ecran);
    }
}
